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
    textureCoord = aTexCoord;
    
    mat4 viewModel = view * model;

    // Calcular matriz de tangentes y bitangentes de normales
    tbNormal = mat3(normalize(mat3(viewModel) * aTangent), normalize(mat3(viewModel) * aBitangent), normalize(mat3(viewModel) * aNormal));

    fragmentPosition = vec3(model * vec4(aPosition, 1.0));

    gl_Position = projection * view * vec4(fragmentPosition, 1.0);
}