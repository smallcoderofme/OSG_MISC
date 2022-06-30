#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 osg_ModelViewProjectionMatrix;
uniform mat4 osg_ModelViewMatrix;
uniform mat4 osg_ViewMatrixInverse;
uniform mat3 osg_NormalMatrix;
uniform mat4 osg_ViewMatrix;

void main()
{
    gl_Position = osg_ModelViewProjectionMatrix * vec4(aPos, 1.0);

}