#pragma once
#include <osg/Group>
#include <osg/Camera>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>

#include <iostream>

#ifndef MUTIPLE_LIGHT_H
#define MUTIPLE_LIGHT_H

class MultipleLights
{
public:
	MultipleLights(osg::Group* root, osg::Camera* camera);

	~MultipleLights();

	osg::Group* _root; osg::Camera* _camera;

	void CreateModel();

	void CreateTextures(osg::Node* node, std::string imagePath, unsigned int unit);

	void CreateShaders(osg::Node* node, osg::MatrixTransform* rootTransForm);

	void CreateShadersForLight(osg::Node* node);

	void CreateLightGeom(osg::MatrixTransform* root, osg::Vec3 lightVecPos, osg::Shape* shape);

	std::string get_file_string(std::string filePath);
};

#endif // !MUTIPLE_LIGHT_H

