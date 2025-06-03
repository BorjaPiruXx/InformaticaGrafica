#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

uniform mat3 normal;
uniform mat4 model, view, projection;

out vec2 textureCoord;
out vec3 fragmentPosition, normalPosition;
out mat3 tbNormal;

void main()
{
    mat4 viewModel = view * model;

    tbNormal = mat3(normalize(mat3(viewModel) * aTangent), normalize(mat3(viewModel) * aBitangent), normalize(mat3(viewModel) * aNormal));

    normalPosition = mat3(transpose(inverse(viewModel))) * aNormal;
    fragmentPosition = vec3(viewModel * vec4(aPosition, 1.0));

    gl_Position = projection * vec4(aPosition, 1.0);
}