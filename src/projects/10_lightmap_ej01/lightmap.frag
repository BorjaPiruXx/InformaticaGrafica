#version 330 core

struct Light
{
    vec3 position, ambient, diffuse, specular;
};

struct Material
{
    int shininess;
    vec3 ambient;
    sampler2D diffuse, specular, emissive;
};

uniform vec3 cameraPosition;
uniform Light light;
uniform Material material;

in vec2 textureCoord;
in vec3 fragmentPosition, normalPosition;
out vec4 fragmentColor;

void main()
{
    vec3 diffMap = vec3(texture(material.diffuse, textureCoord));

    // Invertir mapa especular
    vec3 specMap = vec3(texture(material.specular, textureCoord));
    specMap = vec3(1.0) - specMap;

    // Mapa emisivo
    vec3 emisMap = vec3(texture(material.emissive, textureCoord));
    
    vec3 ambient = diffMap * light.ambient;

    vec3 N = normalize(normalPosition);
    vec3 L = normalize(light.position - fragmentPosition);
    vec3 diffuse = max(dot(N, L), 0.0) * diffMap * light.diffuse;

    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * specMap * light.specular;

    // Controlar intesidad del mapa emisivo
    vec3 emissive = emisMap * 1.5;

    vec3 compLight = ambient + diffuse + specular + emissive;

    fragmentColor = vec4(compLight, 1.0);
}