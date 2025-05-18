#version 330 core

in vec2 textureCoord;
out vec4 fragmentColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    fragmentColor = mix(texture(texture1, textureCoord), texture(texture2, textureCoord), 0.7);
}