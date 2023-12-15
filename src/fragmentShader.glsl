#version 330 core

out vec4 FragColor;
in vec2 textureCoord;

uniform sampler2D textureDiffuse1;

void main()
{
    FragColor = texture(textureDiffuse1, textureCoord);
}