#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "stb_image.h"
#include "engine/input.hpp"

#include "engine/window.hpp"
#include "engine/shader.hpp"
#include "engine/texture.hpp"
#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/geometry/quad.hpp"
#include "engine/geometry/sphere.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

//////////////// Direcciones ////////////////

glm::vec3 dirLightDirection(-0.2f, -1.0f, -0.3f);

std::vector<glm::vec3> spotLightsDirections =
{
    glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f)
};

//////////////// Posiciones ////////////////

std::vector<glm::vec3> pointLightsPositions =
{
    glm::vec3(0.0f, 2.0f, -4.0f),
    glm::vec3(0.0f, 2.0f, 4.0f)
};

std::vector<glm::vec3> spotLightsPositions =
{
    glm::vec3(4.0f, 2.0f, 0.0f),
    glm::vec3(-4.0f, 2.0f, 0.0f)
};

//////////////// Colores ////////////////

glm::vec3 dirLightColor(0.3f, 0.3f, 0.3f);

std::vector<glm::vec3> pointLightsColors =
{
    glm::vec3(0.8f, 0.2f, 0.3f),
    glm::vec3(0.6f, 0.1f, 0.2f)
};

std::vector<glm::vec3> spotLightsColors =
{
    glm::vec3(0.2f, 0.8f, 0.3f),
    glm::vec3(0.2f, 0.1f, 0.8f)
};

bool firstMouse = true;
float lastX, lastY;
float yaw = -90.0f;
float pitch = 0.0f;

const float near = 0.1f;
const float far = 100.0f;

void onMouseMove(float x, float y) 
{
    if (firstMouse) 
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    camera.handleMouseMovement(xoffset, yoffset);
}

void onScrollMove(float xOffset, float yOffset) 
{
    camera.handleMouseScroll(yOffset);
}

void handleInput(float deltaTime) 
{
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W))
        camera.handleKeyboard(Camera::Movement::Forward, deltaTime);
    if (input->isKeyPressed(GLFW_KEY_S))
        camera.handleKeyboard(Camera::Movement::Backward, deltaTime);
    if (input->isKeyPressed(GLFW_KEY_A))
        camera.handleKeyboard(Camera::Movement::Left, deltaTime);
    if (input->isKeyPressed(GLFW_KEY_D))
        camera.handleKeyboard(Camera::Movement::Right, deltaTime);
}

// Establece todas las matrices (vista, proyección modelo y normal) en sus respectivos shaders
void setMatrixOnShader(const  glm::mat4 view, const glm::mat4 proj, glm::vec3 coords, const Shader& shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, coords);
    shader.use();
    shader.set("view", view);
    shader.set("projection", proj);
    shader.set("model", model);
}

// Establece el modelo y tipo de iluminación del shader
void setModelAndTypeOnShader(int light, const Shader& shader)
{
    shader.set("lightModel", light);
    shader.set("lightType", light);
}

// Usa la textura que contenga cada shader
void useTexturesOnShader(bool useTextures, const Shader& shader, const Texture& texture1, const Texture& texture2)
{
    shader.set("material.shininess", 32.0f);

    shader.set("useTextures", useTextures);
    if(useTextures)
    {
        texture1.use(shader, "material.diffuse", 0);
        texture2.use(shader, "material.specular", 1);
    }
}

// Usa la textura para incluir normal mapping
void useNormalMapOnShader(bool useNormalMap, const Shader& shader, const Texture& texture)
{
    shader.set("useNormalMap", useNormalMap);
    if(useNormalMap)
    {
        texture.use(shader, "material.normal", 2);
    }
}

void render(const Geometry& sphere1, const Geometry& sphere2, const Geometry& sphere3, const Geometry& sphere4, 
    const Shader& shader1, const Shader& shader2, const Shader& shader3, const Shader& shader4, 
    const Texture& texture1, const Texture& texture2, const Texture& texture3) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    Window* window = Window::instance();
    const glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);
    
    {
        // Esfera 1 (luz direccional y shader de flat)
        setMatrixOnShader(view, proj, glm::vec3(-3.0f, 1.0f, 0.0f), shader1);
        setModelAndTypeOnShader(0, shader1);
        shader1.set("lightDirection", dirLightDirection);
        shader1.set("lightColor", dirLightColor);
        useTexturesOnShader(false, shader1, texture1, texture2);
        useNormalMapOnShader(false, shader1, texture3);
        sphere1.render();
    }

    {
        // Esfera 2 (PointLight y shader de gouraud)
        setMatrixOnShader(view, proj, glm::vec3(0.0f, 1.0f, 0.0f), shader2);
        setModelAndTypeOnShader(1, shader2);
        shader2.set("lightPosition", pointLightsPositions[0]);
        shader2.set("lightColor", pointLightsColors[0]);
        useTexturesOnShader(false, shader2, texture1, texture2);
        useNormalMapOnShader(false, shader2, texture3);
        sphere2.render();
    }

    {
        // Esfera 3 (SpotLight y shader de phong en espacio de vista)
        setMatrixOnShader(view, proj, glm::vec3(3.0f, 1.0f, 0.0f), shader3);
        setModelAndTypeOnShader(2, shader3);
        shader3.set("lightPosition", spotLightsPositions[0]);
        shader3.set("lightDirection", spotLightsDirections[0]);
        shader3.set("lightColor", spotLightsColors[0]);
        shader3.set("cameraPosition", camera.getPosition());
        useTexturesOnShader(false, shader3, texture1, texture2);
        useNormalMapOnShader(false, shader3, texture3);
        sphere3.render();
    }

    {
        // Esfera 4 (mapas de textura difusa y de normales)
        setMatrixOnShader(view, proj, glm::vec3(0.0f, -1.2f, 0.0f), shader4);
        setModelAndTypeOnShader(2, shader4);
        shader4.set("lightPosition", spotLightsPositions[1]);
        shader4.set("lightDirection", spotLightsDirections[1]);
        shader4.set("lightColor", spotLightsColors[1]);
        shader4.set("cameraPosition", camera.getPosition());
        useTexturesOnShader(true, shader4, texture1, texture2);
        useNormalMapOnShader(true, shader4, texture3);
        sphere4.render();
    }
}

int main(int, char* []) 
{
    system("chcp 65001");
    
    Window* window = Window::instance();
    Input* input = Input::instance();

    input->setMouseMoveCallback(onMouseMove);
    input->setScrollMoveCallback(onScrollMove);

    const Sphere flat(0.5f, 50, 50);
    const Sphere gouraud(0.5f, 50, 50);
    const Sphere phong(0.5f, 50, 50);
    const Sphere normal(0.5f, 50, 50);

    const Shader flat_shader(PROJECT_PATH "lightemitter.vert", PROJECT_PATH "lightemitter.frag");
    const Shader gouraud_shader(PROJECT_PATH "lightemitter.vert", PROJECT_PATH "lightemitter.frag");
    const Shader phong_shader(PROJECT_PATH "lightemitter.vert", PROJECT_PATH "lightemitter.frag");
    const Shader normal_shader(PROJECT_PATH "lightemitter.vert", PROJECT_PATH "lightemitter.frag");

    const Texture bricks_albedo(ASSETS_PATH "textures/bricks_albedo.png", Texture::Format::RGB);
    const Texture bricks_specular(ASSETS_PATH "textures/bricks_specular.png", Texture::Format::RGB);
    const Texture bricks_normal(ASSETS_PATH "textures/bricks_normal.png", Texture::Format::RGB);

    glClearColor(0.0f, 0.2f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    float lastFrame = 0.0f;

    while (window->isAlive()) 
    {
        const auto currentFrame = static_cast<float>(glfwGetTime());
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime);
        //update();
        render(flat, gouraud, phong, normal, flat_shader, gouraud_shader, phong_shader, normal_shader, bricks_albedo, bricks_specular, bricks_normal);
        window->frame();
    }

    return 0;
}