#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform vec3 lightPosition;
uniform mat3 normal;
uniform mat4 model, view, projection;

out vec3 fragmentPosView, normalPosView;

void main()
{
    // Posición del vértice en espacio de vista
    vec4 positionView = view * model * vec4(aPosition, 1.0);
    fragmentPosView = positionView.xyz;

    // Normal en espacio de vista
    normalPosView = normalize(mat3(view * model) * aNormal);

    // Coordenadas finales
    gl_Position = projection * positionView;
}