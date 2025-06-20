#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform mat3 normal;
uniform mat4 model, view, projection;

out vec2 textureCoord;
out vec3 fragmentPosition, normalPosition;

void main()
{
    textureCoord = aTexCoord;
    
    mat4 viewModel = view * model;
    normalPosition = mat3(transpose(inverse(viewModel))) * aNormal;
    fragmentPosition = vec3(viewModel * vec4(aPosition, 1.0));

    gl_Position = projection * vec4(fragmentPosition, 1.0);
}