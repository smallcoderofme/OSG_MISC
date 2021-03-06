#version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aNormal;

layout (location = 3) in vec4 aTexCoords;



out vec3 FragPos;

out vec3 Normal;

out vec2 TexCoords;



uniform mat4 osg_ModelViewProjectionMatrix;

uniform mat4 osg_ModelViewMatrix;

uniform mat4 osg_ViewMatrixInverse;

uniform mat3 osg_NormalMatrix;

uniform mat4 osg_ViewMatrix;



void main()

{

 mat4 newModel = osg_ViewMatrixInverse * osg_ModelViewMatrix;

 FragPos = vec3(newModel * vec4(aPos, 1.0));

 Normal = mat3(transpose(inverse(newModel))) * aNormal;

 TexCoords = aTexCoords.xy;



 gl_Position = osg_ModelViewProjectionMatrix * vec4(aPos, 1.0);



}
