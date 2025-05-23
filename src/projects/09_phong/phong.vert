#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform mat3 normal;
uniform mat4 model, view, projection;

out vec3 fragmentPosition, normalPosition;

void main()
{
    normalPosition = normal * aNormal;
    fragmentPosition = vec3(model * vec4(aPosition, 1.0));
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}