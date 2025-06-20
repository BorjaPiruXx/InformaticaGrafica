#version 330 core

struct Light
{
    vec3 position, ambient, diffuse, specular;
};

struct Material
{
    float shininess;
    vec3 specular;
};

uniform vec3 cameraPosition;
uniform Light light;
uniform Material material;
uniform sampler2D material_diffuse;

in vec2 textureCoord;
in vec3 fragmentPosition, normalPosition;
out vec4 fragmentColor;

void main()
{
    vec3 diffMap = texture(material_diffuse, textureCoord).rgb;

    vec3 ambient = diffMap * light.ambient;

    vec3 N = normalize(normalPosition);
    vec3 L = normalize(light.position - fragmentPosition);
    vec3 diffuse = max(dot(N, L), 0.0) * diffMap * light.diffuse;

    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * material.specular * light.specular;

    fragmentColor = vec4(ambient + diffuse + specular, 1.0);
}