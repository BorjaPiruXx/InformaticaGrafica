#version 330 core

out vec4 fragmentColor;

in vec2 textureCoord;
uniform sampler2D screen;

void main()
{
    fragmentColor = vec4(texture(screen, textureCoord).rgb, 1.0);
}