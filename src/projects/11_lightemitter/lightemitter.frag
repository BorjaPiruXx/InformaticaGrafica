#version 330 core

#define NUM_POINTLIGHTS 2
#define NUM_SPOTLIGHTS 2

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    float constant;
    float lineal;
    float quadratic;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
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

uniform DirLight dirLight;
uniform PointLight pointLights[NUM_POINTLIGHTS];
uniform SpotLight spotLights[NUM_SPOTLIGHTS];
uniform Material material;
uniform vec3 cameraPosition;

in vec2 textureCoord;
in vec3 fragmentPosition, normalPosition;
out vec4 fragmentColor;

vec3 calculateDirLight(DirLight light, vec3 N, vec3 V, vec3 diffMap, vec3 specMap)
{
    vec3 ambient = diffMap * light.ambient;

    vec3 L = normalize(-light.direction);
    vec3 diffuse = max(dot(N, L), 0.0) * diffMap * light.diffuse;

    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * specMap * light.specular;

    return (ambient + diffuse + specular);
}

vec3 calculatePointLight(PointLight light, vec3 N, vec3 V, vec3 fragmentPosition, vec3 diffMap, vec3 specMap)
{
    vec3 direction = light.position - fragmentPosition;
    float distAtt = length(direction);
    float attenuation = 1.0 / (light.constant + (light.lineal * distAtt) + (light.quadratic * pow(distAtt, 2)));

    vec3 ambient = diffMap * light.ambient;

    vec3 L = normalize(direction);
    vec3 diffuse = max(dot(N, L), 0.0) * diffMap * light.diffuse;

    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * specMap * light.specular;

    return ((ambient + diffuse + specular) * attenuation);
}

vec3 calculateSpotLight(SpotLight light, vec3 N, vec3 V, vec3 fragmentPosition, vec3 diffMap, vec3 specMap)
{
    vec3 direction = light.position - fragmentPosition;
    float distAtt = length(direction);
    float attenuation = 1.0 / (light.constant + (light.lineal * distAtt) + (light.quadratic * pow(distAtt, 2)));
    
    vec3 ambient = diffMap * light.ambient;

    vec3 L = normalize(direction);
    vec3 diffuse = max(dot(N, L), 0.0) * diffMap * light.diffuse;

    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * specMap * light.specular;

    float theta = dot(L, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    return ((ambient + (diffuse * intensity) + (specular * intensity)) * attenuation);
}

void main()
{
    vec3 diffMap = vec3(texture(material.diffuse, textureCoord));
    vec3 specMap = vec3(texture(material.specular, textureCoord));

    vec3 N = normalize(normalPosition);
    vec3 V = normalize(cameraPosition - fragmentPosition);

    // Emisor de luz direccional
    vec3 compLight = calculateDirLight(dirLight, N, V, diffMap, specMap);
    
    // Emisores de luz Point Light
    for(int i = 0; i < NUM_POINTLIGHTS; ++i)
    {
        compLight += calculatePointLight(pointLights[i], N, V, fragmentPosition, diffMap, specMap);
    }

    // Emisores de luz Spot Light
    for(int i = 0; i < NUM_SPOTLIGHTS; ++i)
    {
        compLight += calculateSpotLight(spotLights[i], N, V, fragmentPosition, diffMap, specMap);
    }
    
    fragmentColor = vec4(compLight, 1.0);
}