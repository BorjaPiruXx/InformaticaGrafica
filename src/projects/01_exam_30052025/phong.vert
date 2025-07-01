#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform mat4 model, view, projection;

out vec2 textureCoord;
out vec3 fragmentPosition, normal;

void main()
{
    textureCoord = aTexCoord;

    fragmentPosition = vec3(model * vec4(aPosition, 1.0));
    normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * vec4(fragmentPosition, 1.0);
}
