#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

#include <engine/window.hpp>
#include <engine/shader.hpp>
#include <engine/texture.hpp>
#include <engine/input.hpp>
#include <engine/camera.hpp>
#include <engine/geometry/cube.hpp>
#include <engine/geometry/sphere.hpp>
#include <engine/geometry/quad.hpp>

#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

// Dirección de la luz direccional
glm::vec3 dirLightDirection(-0.2f, -1.0f, -0.3f);

// Direcciones del vector de Spot Lights
std::vector<glm::vec3> spotLightsDirections =
{
    glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f)
};

// Posiciones del vector de Point Lights
std::vector<glm::vec3> pointLightsPositions =
{
    glm::vec3(0.0f, 2.0f, -4.0f),
    glm::vec3(0.0f, 2.0f, 4.0f)
};

// Posiciones del vector de Spot Lights
std::vector<glm::vec3> spotLightsPositions =
{
    glm::vec3(4.0f, 2.0f, 0.0f),
    glm::vec3(-4.0f, 2.0f, 0.0f)
};

// Color de la luz direccional
glm::vec3 dirLightColor(0.3f, 0.3f, 0.3f);

// Colores del vector de Point Lights
std::vector<glm::vec3> pointLightsColors =
{
    glm::vec3(0.8f, 0.2f, 0.3f),
    glm::vec3(0.6f, 0.1f, 0.2f)
};

// Colores del vector de Spot Lights
std::vector<glm::vec3> spotLightsColors =
{
    glm::vec3(0.2f, 0.8f, 0.3f),
    glm::vec3(0.2f, 0.1f, 0.8f)
};

std::vector<glm::vec3> battlements
{
    glm::vec3(0.0f, 0.0f, -4.0f),
    glm::vec3(0.0f, 0.0f, 4.0f),
    glm::vec3(-4.0f, 0.0f, 0.0f),
    glm::vec3(4.0f, 0.0f, 0.0f),
    glm::vec3(-4.0f, 0.0f, -4.0f),
    glm::vec3(-4.0f, 0.0f, 4.0f),
    glm::vec3(4.0f, 0.0f, -4.0f),
    glm::vec3(4.0f, 0.0f, 4.0f)
};

bool firstMouse = true;
float lastMouseX, lastMouseY;
float pitch = 0.0f;
float yaw = -90.0f;

const float near = 0.1f;
const float far = 100.0f;

void onMouseMove(const float x, const float y)
{
    if(firstMouse)
    {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }

    float offsetX = x - lastMouseX;
    float offsetY = lastMouseY - y;
    lastMouseX = x;
    lastMouseY = y;

    camera.handleMouseMovement(offsetX, offsetY);
}

void onScrollMove(const float offsetX, const float offsetY)
{
    camera.handleMouseScroll(offsetY);
}

void handleInput(const float time)
{
    Input* input = Input::instance();

    if(input->isKeyPressed(GLFW_KEY_W))
    {
        camera.handleKeyboard(Camera::Movement::Forward, time);
    }

    if(input->isKeyPressed(GLFW_KEY_S))
    {
        camera.handleKeyboard(Camera::Movement::Backward, time);
    }

    if(input->isKeyPressed(GLFW_KEY_D))
    {
        camera.handleKeyboard(Camera::Movement::Left, time);
    }

    if(input->isKeyPressed(GLFW_KEY_A))
    {
        camera.handleKeyboard(Camera::Movement::Right, time);
    }
}

void renderBulbs(const Shader& shader, const Geometry& figure, std::vector<glm::vec3> positions, const std::vector<glm::vec3> colors)
{
    for(size_t i = 0; i < pointLightsPositions.size(); ++i)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, positions[i]);
        model = glm::scale(model, glm::vec3(0.1f));

        shader.set("model", model);
        shader.set("lightColor", colors[i]);

        figure.render();
    }
}

void renderFloor(const Shader& shader, const Geometry& figure, const Texture& texture)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f));
    const glm::mat3 normal = glm::transpose(glm::inverse(model));

    shader.set("model", model);
    shader.set("normal", normal);

    texture.use(shader, "material.diffuse", 0);
    shader.set("material.specular", glm::vec3(0.8f, 0.4f, 0.2f));

    figure.render();
}

void renderBattlements(const Shader& shader, const Geometry& figure, const Texture& texture)
{
    for(auto& battlement : battlements)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, battlement);
        const glm::mat3 normal = glm::transpose(glm::inverse(model));
        shader.set("model", model);
        shader.set("normal", normal);

        texture.use(shader, "material.diffuse", 0);
        texture.use(shader, "material.specular", 1);

        figure.render();
    }
}

void render(const Shader& shader1, const Shader& shader2, const Geometry& figure1, const Geometry& figure2, const Geometry& figure3, const Texture& texture1, const Texture& texture2, const Texture& texture3)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    Window* window = Window::instance();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

    shader1.use();

    shader1.set("view", view);
    shader1.set("projection", projection);

    renderBulbs(shader1, figure1, pointLightsPositions, pointLightsColors);
    renderBulbs(shader1, figure1, spotLightsPositions, spotLightsColors);
    
    shader2.use();
    
    shader2.set("view", view);
    shader2.set("projection", projection);

    // Establecer en shader de phong las componentes asociadas al foco direccional
    shader2.set("dirLight.direction", dirLightDirection);
    shader2.set("dirLight.ambient", dirLightColor * glm::vec3(0.025f));
    shader2.set("dirLight.diffuse", dirLightColor * glm::vec3(0.8f));
    shader2.set("dirLight.specular", dirLightColor * glm::vec3(1.0f, 1.0f, 1.0f));
    
    // Establecer en shader de phong las componentes asociadas al vector de Point Lights
    for(size_t i = 0; i < pointLightsPositions.size(); ++i)
    {
        const std::string pointLight = "pointLights[" + std::to_string(i) + "].";
        shader2.set((pointLight + "position").c_str(), pointLightsPositions[i]);

        shader2.set((pointLight + "ambient").c_str(), pointLightsColors[i] * glm::vec3(0.025f));
        shader2.set((pointLight + "diffuse").c_str(), pointLightsColors[i] * glm::vec3(0.8f));
        shader2.set((pointLight + "specular").c_str(), pointLightsColors[i] * glm::vec3(1.0f, 1.0f, 1.0f));

        shader2.set((pointLight + "constant").c_str(), 1.0f);
        shader2.set((pointLight + "lineal").c_str(), 0.35f);
        shader2.set((pointLight + "quadratic").c_str(), 0.44f);
    }

    // Establecer en shader de phong las componentes asociadas al vector de Spot Lights
    for(size_t i = 0; i < spotLightsPositions.size(); ++i)
    {
        const std::string spotLight = "spotLights[" + std::to_string(i) + "].";

        shader2.set((spotLight + "position").c_str(), spotLightsPositions[i]);
        shader2.set((spotLight + "direction").c_str(), spotLightsDirections[i]);

        shader2.set((spotLight + "cutOff").c_str(), glm::cos(glm::radians(30.0f)));
        shader2.set((spotLight + "outerCutOff").c_str(), glm::cos(glm::radians(35.0f)));

        shader2.set((spotLight + "ambient").c_str(), spotLightsColors[i] * glm::vec3(0.025f));
        shader2.set((spotLight + "diffuse").c_str(), spotLightsColors[i] * glm::vec3(0.8f));
        shader2.set((spotLight + "specular").c_str(), spotLightsColors[i] * glm::vec3(1.0f, 1.0f, 1.0f));

        shader2.set((spotLight + "constant").c_str(), 1.0f);
        shader2.set((spotLight + "lineal").c_str(), 0.35f);
        shader2.set((spotLight + "quadratic").c_str(), 0.44f);
    }
    
    shader2.set("material.shininess", 32);

    shader2.set("cameraPosition", camera.getPosition());

    renderFloor(shader2, figure2, texture1);
    renderBattlements(shader2, figure3, texture2);
}

int main(int, char*[]) 
{
    system("chcp 65001");

    Window* window = Window::instance();
    Input* input = Input::instance();

    input->setMouseMoveCallback(onMouseMove);
    input->setScrollMoveCallback(onScrollMove);

    const Sphere sphere(0.5f, 50, 50);
    const Quad quad(1.0f);
    const Cube cube(1.0f);

    const Shader shader1(PROJECT_PATH "light.vert", PROJECT_PATH "light.frag");
    const Shader shader2(PROJECT_PATH "lightemitter.vert", PROJECT_PATH "lightemitter.frag");

    const Texture texture1(ASSETS_PATH "textures/bricks_albedo.png", Texture::Format::RGB);
    const Texture texture2(ASSETS_PATH "textures/bricks_specular.png", Texture::Format::RGB);
    const Texture texture3(ASSETS_PATH "textures/bricks_normal.png", Texture::Format::RGB);

    glClearColor(0.0f, 0.2f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float lastFrame = 0.0f;
    while(window->isAlive())
    {
        const auto currentFrame = static_cast<float>(glfwGetTime());
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime);
        //update();
        render(shader1, shader2, sphere, quad, cube, texture1, texture2, texture3);
        window->frame();
    }

    return 0;
}