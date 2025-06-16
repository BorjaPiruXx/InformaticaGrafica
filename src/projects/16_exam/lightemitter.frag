#version 330 core

struct Material
{
    float shininess;
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
};

uniform int lightModel, lightType;
uniform bool useTextures, useNormalMap;
uniform vec3 lightPosition, cameraPosition, lightDirection, lightColor;
uniform Material material;

in vec2 textureCoord;
in vec3 fragmentPosition, normalPosition, gouraudColor;
in mat3 tbn;
out vec4 fragmentColor;

vec3 calculateLight(vec3 N, vec3 F, vec2 T)
{
    vec3 light;
    float attenuation = 1.0;
    float intensity = 1.0;

    if(lightType == 0)
    {
        light = normalize(-lightDirection);
    } else
    {
        light = normalize(lightPosition - F);

        float dist = length(lightPosition - F);
        attenuation = 1.0 / (1.0 + 0.09 * dist + 0.032 * (pow(dist, 2)));

        if (lightType == 2) 
        {
            float theta = dot(light, normalize(-lightDirection));
            float outerCutOff = cos(radians(17.5));
            intensity = clamp((theta - outerCutOff) / (cos(radians(12.5)) - outerCutOff), 0.0, 1.0);
        }
    }

    // Normal Mapping
    if(useNormalMap)
    {
        /*vec3 tangentN = vec3(texture(material.normal, T));
        tangentN = normalize(tangentN * 2.0 - 1.0);
        N = normalize(tbn * tangentN);*/
    }

    vec3 V = normalize(cameraPosition - F);
    vec3 R = reflect(-light, N);

    float diff = max(dot(N, light), 0.0);

    vec3 H = normalize(light + V);
    float spec = pow(max(dot(N, H), 0.0), material.shininess);
    
    vec3 ambient = 0.1 * lightColor;
    vec3 diffuse = diff * lightColor;
    vec3 specular = spec * lightColor;

    if(useTextures)
    {
        vec3 diffMap = vec3(texture(material.diffuse, T));
        ambient *= diffMap;
        diffuse *= diffMap;

        vec3 specMap = vec3(texture(material.specular, T));
        specular *= specMap;
    }

    return (ambient + diffuse + specular) * attenuation * intensity;
}

void main()
{
    vec3 light;
    if (lightModel == 1) 
    {
        light = gouraudColor;
    } else
    {
        light = calculateLight(normalize(normalPosition), fragmentPosition, textureCoord);
    }
    
    fragmentColor = vec4(light, 1.0);
}