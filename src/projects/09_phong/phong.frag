#version 330 core

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material
{
    int shininess;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;
uniform vec3 cameraPosition;

in vec3 fragmentPosition, normalPosition;
out vec4 fragmentColor;

void main()
{
    vec3 ambient = material.ambient * light.ambient;

    vec3 N = normalize(normalPosition);
    vec3 L = normalize(light.position - fragmentPosition);
    vec3 diffuse = max(dot(N, L), 0.0) * material.diffuse * light.diffuse;

    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * material.specular * light.specular;

    fragmentColor = vec4(ambient + diffuse + specular, 1.0);
}