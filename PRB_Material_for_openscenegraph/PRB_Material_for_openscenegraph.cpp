// PRB_Material_for_openscenegraph.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgViewer/ViewerEventHandlers>


#include <osg/Geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/Camera>

#include <osgUtil/Optimizer>

#include <osgDB/WriteFile>
#include <osg\LineWidth>
#include <osg/io_utils>
#include <osg/Array>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>


#include <algorithm>

using namespace std;

//void displayStatHandler(osgViewer::Viewer& viewer)
//{
//    osgViewer::StatsHandler* pStatsHandler = new osgViewer::StatsHandler;
//    pStatsHandler->setKeyEventTogglesOnScreenStats(osgGA::GUIEventAdapter::KEY_F11);
//    viewer.addEventHandler(pStatsHandler);
//    viewer.setUpViewInWindow(100, 100, 1200, 900);
//    //osg::DisplaySettings::instance()->setNumMultiSamples(4);
//}

const int OSG_WIDTH = 1280;
const int OSG_HEIGHT = 960;
const osg::Vec4f FOG_COLOR = osg::Vec4f(0.6f, 0.6f, 0.7f, 1.f);



class LogFileHandler : public osg::NotifyHandler
{
public:
	LogFileHandler(const char* filename) { }
	void notify(osg::NotifySeverity severity, const char* message)
	{
		//if (severity == osg::NotifySeverity::ALWAYS)
		//std::cout << message << std::endl;
	}

protected:
	~LogFileHandler() { }
};




osg::ref_ptr<osg::Geode> CreateSphere()
{

	osg::ref_ptr<osg::Geode> node = new osg::Geode();

	osg::ref_ptr<osg::Vec2Array> uv = new osg::Vec2Array;
	osg::ref_ptr<osg::Vec3Array> positions = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP);
	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;
	const float PI = 3.14159265359;
	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
	{
		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			positions->push_back(osg::Vec3(xPos, yPos, zPos));
			uv->push_back(osg::Vec2(xSegment, ySegment));
			normals->push_back(osg::Vec3(xPos, yPos, zPos));
		}
	}

	bool oddRow = false;
	for (int y = 0; y < Y_SEGMENTS; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (int x = 0; x <= X_SEGMENTS; ++x)
			{
				indices->push_back(y * (X_SEGMENTS + 1) + x);
				indices->push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; --x)
			{
				indices->push_back((y + 1) * (X_SEGMENTS + 1) + x);
				indices->push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	int indexCount = indices->size();

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray(positions.get());
	geom->setNormalArray(normals.get(), osg::Array::Binding::BIND_PER_VERTEX);
	geom->setTexCoordArray(0, uv.get(), osg::Array::Binding::BIND_PER_VERTEX);
	//geom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES, 0, 36));
	geom->addPrimitiveSet(indices);
	node->addDrawable(geom);
	return node;
}

class ViewPosCBMultiLightsn : public osg::Uniform::Callback
{
	osg::ref_ptr<osg::Camera> _cam;
public:

	ViewPosCBMultiLightsn(osg::Camera* cam)
	{
		_cam = cam;
	}

	virtual void operator()(osg::Uniform* uniform,
		osg::NodeVisitor* nv)
	{
		osg::Vec3 eye, center, up;
		_cam->getViewMatrixAsLookAt(eye, center, up);

		uniform->set(osg::Vec3(eye.x(), eye.y(), eye.z()));
	}
};

std::string get_file_string(std::string filePath) {
	std::ifstream ifs(filePath);
	return std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
}

float clamp(float x, float upper, float lower)
{
	return min(upper, max(x, lower));
}

void CreateShaders(osg::Node* node, osg::MatrixTransform* rootTransForm, osg::Camera* _camera, float metallic, float roughness)
{

	std::string vertSource = get_file_string("pbr.vert");
	std::string fragSource = get_file_string("pbr.frag");

	osg::ref_ptr<osg::Program> program = new osg::Program;

	program->addShader(new osg::Shader(osg::Shader::VERTEX,
		vertSource));

	program->addShader(new osg::Shader(osg::Shader::FRAGMENT,
		fragSource));

	osg::StateSet* stateset = node->getOrCreateStateSet();  // replace inst with your osg::node

	stateset->setAttributeAndModes(program.get());


	osg::Vec3 eye, center, up;
	_camera->getViewMatrixAsLookAt(eye, center, up);

	stateset->addUniform(new osg::Uniform("albedo", osg::Vec3(1.0f, 1.0f, 0.0f)));
	stateset->addUniform(new osg::Uniform("ao", 1.0f));

	// lights
   // ------
	osg::Vec3 lightPositions[] = {
		osg::Vec3(-10.0f,  10.0f, 10.0f),
		osg::Vec3(10.0f,  10.0f, 10.0f),
		osg::Vec3(-10.0f, -10.0f, 10.0f),
		osg::Vec3(10.0f, -10.0f, 10.0f),
	};
	osg::Vec3 lightColors[] = {
		osg::Vec3(1000.0f, 1000.0f, 1000.0f),
		osg::Vec3(1000.0f, 0.0f, 0.0f),
		osg::Vec3(0.0f, 0.0f, 1000.0f),
		osg::Vec3(0.0f, 1000.0f, 0.0f)
	};

	osg::ref_ptr<osg::Uniform> viewPos = new osg::Uniform(
		"camPos", eye);
	viewPos->setUpdateCallback(new ViewPosCBMultiLightsn(_camera));
	stateset->addUniform(viewPos.get());

	stateset->addUniform(new osg::Uniform("metallic", metallic));
	stateset->addUniform(new osg::Uniform("roughness", roughness));

	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
	{

		std::string s = "pointLights[" + std::to_string(i) + "].position";
		std::string c = "pointLights[" + std::to_string(i) + "].color";

		stateset->addUniform(new osg::Uniform(s.c_str(), lightPositions[i]));
		stateset->addUniform(new osg::Uniform(c.c_str(), lightColors[i]));

	}



}

void CreateMultipleSpheres(osg::MatrixTransform* rootTrans, osg::Camera* cam)
{
	int nrRows = 7;
	int nrColumns = 7;
	float spacing = 2.5;
	osg::Matrix model = osg::Matrix::identity();
	int index = 0;
	for (int row = 0; row < nrRows; ++row)
	{
		float metallic = (float)row / (float)nrRows;
		for (int col = 0; col < nrColumns; ++col)
		{
			// we clamp the roughness to 0.025 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
			// on direct lighting.
			float roughness = clamp((float)col / (float)nrColumns, 0.05f, 1.0f);

			osg::Matrix mat = osg::Matrix::translate(osg::Vec3((col - (nrColumns / 2)) * spacing,
				(row - (nrRows / 2)) * spacing,
				0.0f));

			auto sphere = CreateSphere();
			roughness = index * 0.021f;
			std::cout << "roughness: " << roughness << std::endl;
			CreateShaders(sphere, rootTrans, cam, metallic, roughness);
			osg::ref_ptr<osg::MatrixTransform> sphereTrans = new osg::MatrixTransform;
			sphereTrans->addChild(sphere);
			sphereTrans->setMatrix(mat);
			rootTrans->addChild(sphereTrans);
			++index;
		}
	}

}



void CreateModel(osg::Group* root, osg::Camera* cam)
{
	osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
	CreateMultipleSpheres(trans, cam);
	root->addChild(trans);
}


void CreateSingleView()
{
	osgViewer::Viewer viewer;
	osg::DisplaySettings::instance()->setNumMultiSamples(4);

	osg::ref_ptr<osg::Group> root = new osg::Group();
	auto camera = viewer.getCamera();

	CreateModel(root, camera);

	viewer.setSceneData(root.get());
	//root->addChild(GetGridAndAxis1());
	viewer.setUpViewInWindow(100, 100, OSG_WIDTH, OSG_HEIGHT);

	/* depth settings */
	osg::StateSet* state = root->getOrCreateStateSet();
	state->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

	camera->setClearColor(osg::Vec4(0, 0, 0, 1));
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto manip = new osgGA::TrackballManipulator();
	manip->setVerticalAxisFixed(true);
	manip->setAllowThrow(false);
	camera->getGraphicsContext()->getState()->setUseModelViewAndProjectionUniforms(true);
	camera->getGraphicsContext()->getState()->setUseVertexAttributeAliasing(true);
	viewer.setCameraManipulator(manip);
	osg::ref_ptr<osgGA::StateSetManipulator> statesetManipulator = new osgGA::StateSetManipulator(viewer.getCamera()->getStateSet());
	viewer.addEventHandler(statesetManipulator.get());
	viewer.realize();
	while (!viewer.done()) {
		viewer.frame();
	}
}

int main()
{
//#ifdef _WIN32
//	::SetProcessDPIAware(); // if Windows
//#endif // _WIN32

	osg::setNotifyLevel(osg::NotifySeverity::DEBUG_INFO);
	osg::setNotifyHandler(new LogFileHandler("log.txt"));
	CreateSingleView();

	return 0;
}


//int main()
//{
//    osg::notify(osg::WARN) << "osg start running." << std::endl;
//    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("cessna.osg.0,0,90.rot");
//    //osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("monky.ive");
//    osgViewer::Viewer viewer;
//    displayStatHandler(viewer);
//    viewer.setSceneData(root.get());
//    return viewer.run();
//}

