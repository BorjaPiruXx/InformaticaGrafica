#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model, view, projection;

out vec2 textureCoord;

void main() {
    textureCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}