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
};

struct Material
{
    float shininess;
    vec3 specular;
};

uniform vec3 cameraPosition;
uniform Light light;
uniform FlashLight flashLight;
uniform Material material;
uniform sampler2D material_diffuse;

in vec2 textureCoord;
in vec3 fragmentPosition, normalPosition;
out vec4 fragmentColor;

void main()
{
    vec3 diffMap = texture(material_diffuse, textureCoord).rgb;

    //////////////////// Light /////////////////////

    vec3 ambient = diffMap * light.ambient;

    vec3 N = normalize(normalPosition);
    vec3 L = normalize(light.position - fragmentPosition);
    vec3 diffuse = max(dot(N, L), 0.0) * diffMap * light.diffuse;

    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * material.specular * light.specular;

    vec3 compLight = ambient + diffuse + specular;

    //////////////////// Flash Light /////////////////////

    L = normalize(flashLight.position - fragmentPosition);
    H = normalize(L + V);

    // Atenuar el cono de luz
    float theta = dot(L, normalize(-flashLight.direction));
    float epsilon = flashLight.cutOff - flashLight.outerCutOff;

    // Aplicar intensidad del foco
    float intensity = clamp((theta - flashLight.outerCutOff) / epsilon, 0.0, 1.0);

    ambient = diffMap * flashLight.ambient;
    diffuse = max(dot(N, L), 0.0) * diffMap * flashLight.diffuse;
    specular = pow(max(dot(N, H), 0.0), material.shininess) * material.specular * flashLight.specular;

    compLight += ambient + (diffuse * intensity) + (specular * intensity);

    fragmentColor = vec4(compLight, 1.0);
}