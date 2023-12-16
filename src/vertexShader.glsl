#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTextureCoord;

out vec2 textureCoord;

uniform mat4 matModel;
uniform mat4 matCamera;
uniform mat4 matPerspective;

void main()
{
    textureCoord = vertexTextureCoord;
    gl_Position = matPerspective * matCamera * matModel * vec4(vertexPosition, 1.0);
}