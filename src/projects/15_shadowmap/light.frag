#version 330 core

out vec4 FragColor;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 position;
};
uniform Light light;


void main() {    
    FragColor = vec4(light.specular, 1.0);
}