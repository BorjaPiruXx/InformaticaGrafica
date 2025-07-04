#version 330 core

struct Light
{
    float constant, lineal, quadratic;
    vec3 position, ambient, diffuse, specular;
};

struct Material
{
    int shininess;
    sampler2D diffuse, normal;
};

uniform vec3 cameraPosition;
uniform Light light;
uniform Material material;

in vec2 textureCoord;
in vec3 fragmentPosition;
in mat3 tbn;

out vec4 fragmentColor;

void main()
{
    vec3 diffMap = vec3(texture(material.diffuse, textureCoord)) * 1.5;
    vec3 normMap = vec3(texture(material.normal, textureCoord));

    // Obtener y transformar normal del mapa: [0,1] => [-1,1]
    vec3 N = normalize(tbn * ((normMap * 2.0 - 1.0)) * 1.5);

    vec3 L = normalize(light.position - fragmentPosition);
    vec3 V = normalize(cameraPosition - fragmentPosition);
    vec3 H = normalize(L + V);
    //vec3 R = reflect(-L, N); --> para modelo Phong

    vec3 direction = light.position - fragmentPosition;
    float distAtt = length(direction);
    float attenuation = 1.0 / (light.constant + (light.lineal * distAtt) + (light.quadratic * pow(distAtt, 2)));

    vec3 ambient = light.ambient * diffMap;
    vec3 diffuse = max(dot(N, L), 0.0) * diffMap * light.diffuse;
    vec3 specular = pow(max(dot(N, H), 0.0), material.shininess) * light.specular;
    //vec3 specular = pow(max(dot(V, R), 0.0), material.shininess) * light.specular; --> para modelo Phong

    vec3 compLight = (ambient + diffuse + specular) * attenuation;
    fragmentColor= vec4(compLight, 1.0);
}