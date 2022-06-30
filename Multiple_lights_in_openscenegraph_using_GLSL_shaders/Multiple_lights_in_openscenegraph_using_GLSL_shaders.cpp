// Multiple_lights_in_openscenegraph_using_GLSL_shaders.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iostream>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>

#include "Multiplelights.h"
using namespace std;

const int OSG_WIDTH = 1280;
const int OSG_HEIGHT = 960;
const osg::Vec4f FOG_COLOR = osg::Vec4f(0.6f, 0.6f, 0.7f, 1.f);


int main()
{
	//osg::notify(osg::WARN) << "osg start running." << std::endl;
	//osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("cessna.osg.0,0,90.rot");
	////osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("monky.ive");
	//osgViewer::Viewer viewer;
	//viewer.setSceneData(root.get());
	//viewer.setUpViewInWindow(100, 100, 800, 600);
	//return viewer.run();

//#ifdef _WIN32
//    ::SetProcessDPIAware(); // if Windows
//#endif // _WIN32

    osgViewer::Viewer viewer;
    osg::DisplaySettings::instance()->setNumMultiSamples(4);
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::Camera* camera = viewer.getCamera();
    MultipleLights ml(root.get(), camera);
    ml.CreateModel();
    viewer.setSceneData(root.get());
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
    return 0;
}
