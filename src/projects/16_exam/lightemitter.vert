#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

struct Material
{
    float shininess;
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
};

/*
 * Selección del modelo de iluminación y tipo de luz:
 *  > 0 (Flat y luz direccional)
 *  > 1 (Gouraud y PointLight)
 *  > 2 (Phong y SpotLight)
*/
uniform int lightModel, lightType;

uniform bool useTextures;
uniform vec3 lightPosition, cameraPosition, lightDirection, lightColor;
uniform mat4 model, view, projection;
uniform Material material;

out vec2 textureCoord;
out vec3 normalPosition, fragmentPosition, gouraudColor;

// Matriz TBN (Tangentes-Bitangentes-Normales)
out mat3 tbn;

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

        // Atenuación
        float dist = length(lightPosition - F);
        attenuation = 1.0 / (1.0 + 0.09 * dist + 0.032 * (pow(dist, 2)));

        if (lightType == 2) 
        {
            // Intensidad
            float theta = dot(light, normalize(-lightDirection));
            float outerCutOff = cos(radians(17.5));
            intensity = clamp((theta - outerCutOff) / (cos(radians(12.5)) - outerCutOff), 0.0, 1.0);
        }
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
    textureCoord = aTexCoord;

    // Transformar tangente, bitangente y normal a espacio de vista
    mat3 normal = transpose(inverse(mat3(view * model)));
    normalPosition = normalize(normal * aNormal);
    tbn = mat3(normalize(normal * aTangent), normalize(normal * aBitangent), normalPosition);

    vec4 worldPosition = model * vec4(aPosition, 1.0);
    fragmentPosition = vec3(view * worldPosition);

    // Se calcula el modelo de iluminación Gouraud en el propio shader de vértices
    if (lightModel == 1)
    {
        gouraudColor = calculateLight(normalPosition, fragmentPosition, textureCoord);
    }

    gl_Position = projection * view * worldPosition;
}