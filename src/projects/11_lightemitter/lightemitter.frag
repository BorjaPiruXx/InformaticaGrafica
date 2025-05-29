#version 330 core

struct Light
{
    float constant;
    float lineal;
    float quadratic;
    float cutOff;
    float outerCutOff;
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material
{
    int shininess;
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
};

uniform Light light;
uniform Material material;
uniform vec3 cameraPosition;

in vec2 textureCoord;
in vec3 fragmentPosition, normalPosition;
out vec4 fragmentColor;

void main()
{
    vec3 diffMap = vec3(texture(material.diffuse, textureCoord));
    vec3 specMap = vec3(texture(material.specular, textureCoord));

    vec3 direction = light.position - fragmentPosition;
    float distAtt = length(direction);
    float attenuation = 1.0 / (light.constant + (light.lineal * distAtt) + (light.quadratic * pow(distAtt, 2)));
    
    vec3 ambient = diffMap * light.ambient;

    vec3 N = normalize(normalPosition);
    vec3 L = normalize(direction);
    vec3 diffuse = max(dot(N, L), 0.0) * diffMap * light.diffuse;

    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * specMap * light.specular;

    // Depende de la intensidad de luz que reciba, se irá atenuando más o menos
    float theta = dot(L, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    fragmentColor = vec4((ambient + (diffuse * intensity) + (specular * intensity)) * attenuation, 1.0);
}