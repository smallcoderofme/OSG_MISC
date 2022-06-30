#include "Multiplelights.h"

// #include "stdafx.h"


class ViewPosCBMultiLights : public osg::Uniform::Callback
{

    osg::ref_ptr<osg::Camera> _cam;

public:



    ViewPosCBMultiLights(osg::Camera* cam)
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



MultipleLights::MultipleLights(osg::Group* root, osg::Camera* camera) : _root(root), _camera(camera)
{



}



MultipleLights::~MultipleLights()
{

}

void MultipleLights::CreateModel()
{

    osg::ref_ptr<osg::Vec3Array> vertexArray = new osg::Vec3Array;



    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, -0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, 0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, -0.5f));



    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, -0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, 0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, 0.5f));



    vertexArray->push_back(osg::Vec3(-0.5f, 0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, 0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, 0.5f, 0.5f));



    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, -0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, -0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, -0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, 0.5f));



    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, -0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, -0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, -0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, -0.5f, -0.5f));



    vertexArray->push_back(osg::Vec3(-0.5f, 0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, -0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(0.5f, 0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, 0.5f, 0.5f));

    vertexArray->push_back(osg::Vec3(-0.5f, 0.5f, -0.5f));





    osg::ref_ptr<osg::Vec3Array> normalArray = new osg::Vec3Array;

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));



    normalArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    normalArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));



    normalArray->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));



    normalArray->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));

    normalArray->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));



    normalArray->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));



    normalArray->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));

    normalArray->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));



    osg::ref_ptr<osg::Vec2Array> texCor = new osg::Vec2Array;

    texCor->push_back(osg::Vec2(0.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 1.0f));

    texCor->push_back(osg::Vec2(1.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 0.0f));



    texCor->push_back(osg::Vec2(0.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 1.0f));

    texCor->push_back(osg::Vec2(1.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 0.0f));



    texCor->push_back(osg::Vec2(1.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 0.0f));



    texCor->push_back(osg::Vec2(1.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 1.0f));

    texCor->push_back(osg::Vec2(0.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 0.0f));



    texCor->push_back(osg::Vec2(0.0f, 1.0f));

    texCor->push_back(osg::Vec2(1.0f, 1.0f));

    texCor->push_back(osg::Vec2(1.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 0.0f));

    texCor->push_back(osg::Vec2(0.0f, 0.0f));

    texCor->push_back(osg::Vec2(0.0f, 1.0f));



    texCor->push_back(osg::Vec2(0.0f, 1.0f));

    texCor->push_back(osg::Vec2(1.0f, 1.0f));

    texCor->push_back(osg::Vec2(1.0f, 0.0f));

    texCor->push_back(osg::Vec2(1.0f, 0.0f));

    texCor->push_back(osg::Vec2(0.0f, 0.0f));

    texCor->push_back(osg::Vec2(0.0f, 1.0f));


    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

    geom->setVertexArray(vertexArray.get());

    geom->setNormalArray(normalArray.get(), osg::Array::Binding::BIND_PER_VERTEX);

    geom->setTexCoordArray(0, texCor.get(), osg::Array::Binding::BIND_PER_VERTEX);

    geom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES, 0, 36));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;

    geode->addDrawable(geom);

    std::string diffuseImagePath = "container2.png";

    std::string specularImagePath = "container2_specular.png";

    CreateTextures(geode, diffuseImagePath, 0.0);

    CreateTextures(geode, specularImagePath, 1);

    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;

    trans->addChild(geode);

    CreateShaders(geode, trans);

    _root->addChild(trans);

}

void MultipleLights::CreateTextures(osg::Node* node, std::string imagePath, unsigned int unit)

{

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;

    osg::ref_ptr<osg::Image> image =

        osgDB::readImageFile(imagePath);

    texture->setImage(image.get());

    texture->setWrap(osg::Texture::WrapParameter::WRAP_S, osg::Texture::WrapMode::REPEAT);

    texture->setWrap(osg::Texture::WrapParameter::WRAP_T, osg::Texture::WrapMode::REPEAT);

    texture->setFilter(osg::Texture::FilterParameter::MIN_FILTER, osg::Texture::FilterMode::LINEAR_MIPMAP_LINEAR);

    texture->setFilter(osg::Texture::FilterParameter::MAG_FILTER, osg::Texture::FilterMode::LINEAR);

    node->getOrCreateStateSet()->setTextureAttributeAndModes(unit, texture.get());

}

void MultipleLights::CreateShaders(osg::Node* node, osg::MatrixTransform* rootTransForm)
{

    std::string vertSource = get_file_string("multiplelights.vert");

    std::string fragSource = get_file_string("multiplelights.frag");


    osg::ref_ptr<osg::Program> program = new osg::Program;


    program->addShader(new osg::Shader(osg::Shader::VERTEX,

        vertSource));

    program->addShader(new osg::Shader(osg::Shader::FRAGMENT,

        fragSource));

    osg::StateSet* stateset = node->getOrCreateStateSet();  // replace inst with your osg::node

    stateset->setAttributeAndModes(program.get());

    osg::Vec3 eye, center, up;

    _camera->getViewMatrixAsLookAt(eye, center, up);

    osg::ref_ptr<osg::Uniform> viewPos = new osg::Uniform(

        "viewPos", eye);

    viewPos->setUpdateCallback(new ViewPosCBMultiLights(_camera));

    stateset->addUniform(viewPos.get());


    osg::Uniform* diffuseUniform = new osg::Uniform(osg::Uniform::SAMPLER_2D, "material.diffuse");

    diffuseUniform->set(0);

    stateset->addUniform(diffuseUniform);

    osg::Uniform* specularUniform = new osg::Uniform(osg::Uniform::SAMPLER_2D, "material.specular");

    specularUniform->set(1);

    stateset->addUniform(specularUniform);

    stateset->addUniform(new osg::Uniform("material.shininess", 32.0f));

    osg::Vec3 pointLightPositions[] = {

       osg::Vec3(0.7f,  0.2f,  2.0f),

       osg::Vec3(2.3f, -3.3f, -4.0f),

       osg::Vec3(-4.0f,  2.0f, -12.0f),

       osg::Vec3(0.0f,  0.0f, -3.0f)

    };


    CreateLightGeom(rootTransForm, pointLightPositions[0], new osg::Sphere(osg::Vec3(0, 0, 0), 0.5));

    CreateLightGeom(rootTransForm, pointLightPositions[1], new osg::Sphere(osg::Vec3(0, 0, 0), 0.5));

    CreateLightGeom(rootTransForm, pointLightPositions[2], new osg::Sphere(osg::Vec3(0, 0, 0), 0.5));

    CreateLightGeom(rootTransForm, pointLightPositions[3], new osg::Sphere(osg::Vec3(0, 0, 0), 0.5));



    CreateLightGeom(rootTransForm, osg::Vec3(-0.2f, -1.0f, -0.3f) * 10, new osg::Box(osg::Vec3(0, 0, 0), 0.5));

    CreateLightGeom(rootTransForm, osg::Vec3(5, 5, 5), new osg::Cone(osg::Vec3(0, 0, 0), 0.5, 0.5));







    // directional light

    stateset->addUniform(new osg::Uniform("dirLight.direction", osg::Vec3(-0.2f, -1.0f, -0.3f)));

    stateset->addUniform(new osg::Uniform("dirLight.ambient", osg::Vec3(0.05f, 0.05f, 0.05f)));

    stateset->addUniform(new osg::Uniform("dirLight.diffuse", osg::Vec3(0.4f, 0.4f, 0.4f)));

    stateset->addUniform(new osg::Uniform("dirLight.specular", osg::Vec3(0.5f, 0.5f, 0.5f)));

    // point light 1

    stateset->addUniform(new osg::Uniform("pointLights[0].position", pointLightPositions[0]));

    stateset->addUniform(new osg::Uniform("pointLights[0].ambient", osg::Vec3(0.05f, 0.05f, 0.05f)));

    stateset->addUniform(new osg::Uniform("pointLights[0].diffuse", osg::Vec3(0.8f, 0.8f, 0.8f)));

    stateset->addUniform(new osg::Uniform("pointLights[0].specular", osg::Vec3(1.0f, 1.0f, 1.0f)));

    stateset->addUniform(new osg::Uniform("pointLights[0].constant", 1.0f));

    stateset->addUniform(new osg::Uniform("pointLights[0].linear", 0.09));

    stateset->addUniform(new osg::Uniform("pointLights[0].quadratic", 0.032));

    // point light 2

    stateset->addUniform(new osg::Uniform("pointLights[1].position", pointLightPositions[1]));

    stateset->addUniform(new osg::Uniform("pointLights[1].ambient", osg::Vec3(0.05f, 0.05f, 0.05f)));

    stateset->addUniform(new osg::Uniform("pointLights[1].diffuse", osg::Vec3(0.8f, 0.8f, 0.8f)));

    stateset->addUniform(new osg::Uniform("pointLights[1].specular", osg::Vec3(1.0f, 1.0f, 1.0f)));

    stateset->addUniform(new osg::Uniform("pointLights[1].constant", 1.0f));

    stateset->addUniform(new osg::Uniform("pointLights[1].linear", 0.09));

    stateset->addUniform(new osg::Uniform("pointLights[1].quadratic", 0.032));

    // point light 3

    stateset->addUniform(new osg::Uniform("pointLights[2].position", pointLightPositions[2]));

    stateset->addUniform(new osg::Uniform("pointLights[2].ambient", osg::Vec3(0.05f, 0.05f, 0.05f)));

    stateset->addUniform(new osg::Uniform("pointLights[2].diffuse", osg::Vec3(0.8f, 0.8f, 0.8f)));

    stateset->addUniform(new osg::Uniform("pointLights[2].specular", osg::Vec3(1.0f, 1.0f, 1.0f)));

    stateset->addUniform(new osg::Uniform("pointLights[2].constant", 1.0f));

    stateset->addUniform(new osg::Uniform("pointLights[2].linear", 0.09));

    stateset->addUniform(new osg::Uniform("pointLights[2].quadratic", 0.032));

    // point light 4

    stateset->addUniform(new osg::Uniform("pointLights[3].position", pointLightPositions[3]));

    stateset->addUniform(new osg::Uniform("pointLights[3].ambient", osg::Vec3(0.05f, 0.05f, 0.05f)));

    stateset->addUniform(new osg::Uniform("pointLights[3].diffuse", osg::Vec3(0.8f, 0.8f, 0.8f)));

    stateset->addUniform(new osg::Uniform("pointLights[3].specular", osg::Vec3(1.0f, 1.0f, 1.0f)));

    stateset->addUniform(new osg::Uniform("pointLights[3].constant", 1.0f));

    stateset->addUniform(new osg::Uniform("pointLights[3].linear", 0.09));

    stateset->addUniform(new osg::Uniform("pointLights[3].quadratic", 0.032));

    // spotLight

    osg::Vec3 spotLightPosition = osg::Vec3(5, 5, 5);

    osg::Vec3 spotLightdirection = osg::Vec3() - spotLightPosition;

    spotLightdirection.normalize();



    stateset->addUniform(new osg::Uniform("spotLight.position", spotLightPosition));

    stateset->addUniform(new osg::Uniform("spotLight.direction", spotLightdirection));

    stateset->addUniform(new osg::Uniform("spotLight.ambient", osg::Vec3(0.0f, 0.0f, 0.0f)));

    stateset->addUniform(new osg::Uniform("spotLight.diffuse", osg::Vec3(1.0f, 1.0f, 1.0f)));

    stateset->addUniform(new osg::Uniform("spotLight.specular", osg::Vec3(1.0f, 1.0f, 1.0f)));

    stateset->addUniform(new osg::Uniform("spotLight.constant", 1.0f));

    stateset->addUniform(new osg::Uniform("spotLight.linear", 0.09));

    stateset->addUniform(new osg::Uniform("spotLight.quadratic", 0.032));

    /*stateset->addUniform(new osg::Uniform("spotLight.cutOff", glm::cos(glm::radians(12.5f))));

    stateset->addUniform(new osg::Uniform("spotLight.outerCutOff", glm::cos(glm::radians(15.0f))));

   */

    stateset->addUniform(new osg::Uniform("spotLight.cutOff", 0.9762959977));

    stateset->addUniform(new osg::Uniform("spotLight.outerCutOff", 0.96592592665));

}



void MultipleLights::CreateLightGeom(osg::MatrixTransform* root, osg::Vec3 lightVecPos, osg::Shape* shape)
{

    osg::ref_ptr<osg::MatrixTransform> lightObj = new osg::MatrixTransform;

    osg::ref_ptr<osg::Geode> bxGeode = new osg::Geode;

    bxGeode->addDrawable(new osg::ShapeDrawable(shape));

    lightObj->addChild(bxGeode);

    lightObj->setMatrix(osg::Matrix::translate(lightVecPos));

    root->addChild(lightObj);

    CreateShadersForLight(lightObj);

}

void MultipleLights::CreateShadersForLight(osg::Node* node)
{
    std::string vertSource = get_file_string("lightshader.vert");

    std::string fragSource = get_file_string("lightshader.frag");

    osg::ref_ptr<osg::Program> program = new osg::Program;


    program->addShader(new osg::Shader(osg::Shader::VERTEX,

        vertSource));

    program->addShader(new osg::Shader(osg::Shader::FRAGMENT,

        fragSource));

    osg::StateSet* stateset = node->getOrCreateStateSet();  // replace inst with your osg::node



    stateset->setAttributeAndModes(program.get());

}

std::string MultipleLights::get_file_string(std::string filePath) {

    std::ifstream ifs(filePath);

    return std::string((std::istreambuf_iterator<char>(ifs)),

        (std::istreambuf_iterator<char>()));

}

