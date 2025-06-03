#version 330 core

out vec4 fragmentColor;

in vec2 textureCoord;
uniform sampler2D screenTexture;

void main()
{
    fragmentColor = texture(screenTexture, textureCoord);
}