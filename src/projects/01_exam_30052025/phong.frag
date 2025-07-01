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

uniform bool useTextures;
uniform vec3 cameraPosition;
uniform PointLight light;
uniform Material material;
uniform sampler2D material_diffuse;
uniform sampler2D normalMap;

in vec2 textureCoord;
in vec3 fragmentPosition, normal;
out vec4 fragmentColor;

void main()
{
    //vec3 N = normalize(normal);
    vec3 NTexture = normalize(texture(normalMap, textureCoord).rgb * 2.0 - 1.0);
    vec3 N = normalize(NTexture);
    vec3 L = normalize(light.position - fragmentPosition);
    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 R = reflect(-L, N);

    vec3 ambient = light.ambient;
    vec3 diffuse = max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = pow(max(dot(V, R), 0.0), material.shininess) * light.specular * material.specular;
    vec3 compLight = ambient + diffuse + specular;

    vec4 textureColor = useTextures ? texture(material_diffuse, textureCoord) : vec4(1.0);
    fragmentColor = vec4(compLight, 1.0) * textureColor;
}
