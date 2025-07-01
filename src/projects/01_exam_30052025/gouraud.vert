#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

struct PointLight
{
    vec3 position, ambient, diffuse, specular;
};

struct Material
{
    float shininess;
    vec3 specular;
};

uniform vec3 viewPosition;
uniform mat4 model, view, projection;
uniform PointLight light;
uniform Material material;

out vec2 textureCoord;
out vec3 compLight;

void main()
{
    textureCoord = aTexCoord;

    vec3 fragmentPosition = vec3(model * vec4(aPosition, 1.0));

    vec3 N = normalize(mat3(transpose(inverse(model))) * aNormal);
    vec3 L = normalize(light.position - fragmentPosition);
    vec3 V = normalize(viewPosition - fragmentPosition);
    vec3 R = reflect(-L, N);

    vec3 ambient = light.ambient;
    vec3 diffuse = max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = pow(max(dot(V, R), 0.0), material.shininess) * light.specular * material.specular;
    compLight = ambient + diffuse + specular;

    gl_Position = projection * view * vec4(fragmentPosition, 1.0);
}
