#version 330 core

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
uniform PointLight light;
uniform Material material;
uniform sampler2D material_diffuse;

flat in vec3 fragmentNormal, fragmentPosition;
in vec2 textureCoord;
out vec4 fragmentColor;

void main()
{
    vec3 N = normalize(fragmentNormal);
    vec3 L = normalize(light.position - fragmentPosition);
    vec3 V = normalize(viewPosition - fragmentPosition);
    vec3 R = reflect(-L, N);

    vec3 ambient = light.ambient;
    vec3 diffuse = max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = pow(max(dot(V, R), 0.0), material.shininess) * light.specular * material.specular;
    vec3 compLight = ambient + diffuse + specular;

    fragmentColor = vec4(compLight, 1.0) * vec4(1.0f);
}
