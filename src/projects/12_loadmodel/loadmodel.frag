#version 330 core

uniform sampler2D texture_diffuse1;

in vec2 textureCoord;
out vec4 fragmentColor;

void main() {
    fragmentColor = texture(texture_diffuse1, textureCoord);
}