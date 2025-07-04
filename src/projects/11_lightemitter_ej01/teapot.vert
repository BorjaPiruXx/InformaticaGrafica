#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

uniform mat3 normal;
uniform mat4 model, view, projection;

out vec2 textureCoord;
out vec3 fragmentPosition;
out mat3 tbn;

void main()
{
    vec4 worldPosition = model * vec4(aPosition, 1.0);
    fragmentPosition = vec3(view * worldPosition);
    textureCoord = aTexCoord;
    vec3 T = normalize(normal * aTangent);
    vec3 B = normalize(normal * aBitangent);
    vec3 N = normalize(normal * aNormal);
    tbn = mat3(T, B, N);

    gl_Position = projection * view * worldPosition;
}