#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 textureCoord;

void main()
{
    textureCoord = aTexCoord;
    gl_Position = vec4(aPosition, 1.0);
}