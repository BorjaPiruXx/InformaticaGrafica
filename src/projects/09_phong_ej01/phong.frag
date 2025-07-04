#version 330 core

struct Light
{
    vec3 position, ambient, diffuse, specular;
};

struct Material
{
    int shininess;
    vec3 ambient, diffuse, specular;
};

uniform Light light;
uniform Material material;

in vec3 fragmentPosView, normalPosView;
out vec4 fragmentColor;

void main()
{
    vec3 ambient = material.ambient * light.ambient;

    vec3 N = normalize(normalPosView);
    vec3 L = normalize(light.position - fragmentPosView);
    vec3 diffuse = max(dot(N, L), 0.0) * material.diffuse * light.diffuse;

    // La cámara está en el origen del espacio de vista
    vec3 V = normalize(-fragmentPosView);
    vec3 H = normalize(L + V);
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * material.specular * light.specular;

    vec3 compLight = ambient + diffuse + specular;

    fragmentColor = vec4(compLight, 1.0);
}