#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

uniform mat4 model, view, projection;

out vec2 textureCoord;
flat out vec3 fragmentNormal, fragmentPosition;

void main()
{
    textureCoord = aTexCoord;

    vec4 worldPosition = model * vec4(aPosition, 1.0);
    fragmentPosition = vec3(worldPosition);
    fragmentNormal = mat3(transpose(inverse(model))) * aNormal;
    
    gl_Position = projection * view * worldPosition;
}