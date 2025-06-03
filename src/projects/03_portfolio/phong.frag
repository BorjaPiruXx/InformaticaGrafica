#version 330 core

struct Light
{
    vec3 position, ambient, diffuse, specular;
};

// Nueva luz Flash Light (linterna)
struct FlashLight
{
    float cutOff, outerCutOff;
    
    vec3 position, direction, ambient, diffuse, specular;
}

struct Material
{
    int shininess;
    
    vec3 ambient, diffuse, specular;
};

uniform Light light;
uniform FlashLight flashLihght;
uniform Material material;
uniform vec3 cameraPosition;

in vec3 fragmentPosition, normalPosition;
out vec4 fragmentColor;

void main()
{
    //////////////////// Light /////////////////////

    vec3 ambient = material.ambient * light.ambient;

    vec3 N = normalize(normalPosition);
    vec3 L = normalize(light.position - fragmentPosition);
    vec3 diffuse = max(dot(N, L), 0.0) * material.diffuse * light.diffuse;

    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * material.specular * light.specular;

    vec3 compLight = ambient + diffuse + specular;

    //////////////////// Flash Light /////////////////////
    
    N = normalize(normalPosition);
    V = normalize(cameraPosition - fragmentPosition);
    H = normalize(L + V);

    // Atenuar el cono de luz
    L = normalize(flashLight.position - fragmentPosition);
    float theta = dot(L, normalize(-flashLight.direction));
    float epsilon = flashLight.cutOff - flashLight.outerCutOff;

    ambient = material.ambient * flashLight.ambient;

    diffuse = max(dot(N, L), 0.0) * material.diffuse * flashLight.diffuse;

    specular = pow(max(dot(N, H), 0.0), material.shininess) * material.specular * flashLight.specular;

    // Aplicar intensidad del foco
    float intensity = clamp((theta - flashLight.outerCutOff) / epsilon, 0.0, 1.0);
    compLight += ambient + (diffuse * intensity) + (specular * intensity);

    fragmentColor = vec4(compLight, 1.0);
}