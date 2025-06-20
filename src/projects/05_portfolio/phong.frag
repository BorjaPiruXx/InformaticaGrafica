#version 330 core

struct DirLight
{
    vec3 direction, ambient, diffuse, specular;
};

struct Light
{
    vec3 position, ambient, diffuse, specular;
};

struct Material
{
    float shininess;
};

uniform vec3 cameraPosition;
uniform DirLight dirLight;
uniform Light light;
uniform Material material;
uniform sampler2D material_diffuse, material_specular, material_normal;

in vec2 textureCoord;
in vec3 fragmentPosition, normalPosition;
in mat3 tbNormal;
out vec4 fragmentColor;

void main()
{
    vec3 diffMap = texture(material_diffuse, textureCoord).rgb;
    vec3 specMap = texture(material_specular, textureCoord).rgb;

    vec3 normMap = texture(material_normal, textureCoord).rgb;
    vec3 N = normalize(normMap * 2.0 - 1.0);
    N = normalize(tbNormal * N);

    //////////////////// Directional Light /////////////////////

    vec3 ambient = diffMap * dirLight.ambient;

    vec3 L = normalize(-dirLight.direction);
    vec3 diffuse = max(dot(N, L), 0.0) * diffMap * dirLight.diffuse;

    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * specMap * dirLight.specular;

    vec3 compLight = ambient + diffuse + specular;

    //////////////////// Light /////////////////////

    L = normalize(light.position - fragmentPosition);
    H = normalize(L + V);

    ambient = diffMap * light.ambient;
    diffuse = max(dot(N, L), 0.0) * diffMap * light.diffuse;
    specular = pow(max(dot(N, H), 0.0), material.shininess) * specMap * light.specular;

    compLight += ambient + diffuse + specular;

    fragmentColor = vec4(compLight, 1.0);
}