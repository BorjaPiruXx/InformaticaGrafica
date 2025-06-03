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
#include <engine/geometry/sphere.hpp>

#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

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

void render(const Shader& shader1, const Shader& shader2, const Geometry& figure)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrixWithoutGLM();

    Window* window = Window::instance();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

    glm::vec3 lightPosition = glm::vec3(3.0f, 1.0f, 0.0f);
    glm::vec3 lightColor = glm::vec3(0.5f, 1.0f, 0.5f);

    // Posición de la linterna (posicionada en la cámara)
    glm::vec3 flashPosition = camera.getPosition();

    // Dirección de la linterna (apunta hacia el vector front_ de la cámara)
    glm::vec3 flashDirection = camera.getFront();

    // Color de la linterna (blanca)
    glm::vec3 flashColor = glm::vec3(1.0f);

    glm::vec3 objectColor = glm::vec3(0.8f, 0.4f, 0.2f);

    shader1.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPosition);
    model = glm::scale(model, glm::vec3(0.1f));

    shader1.set("model", model);
    shader1.set("view", view);
    shader1.set("projection", projection);

    shader1.set("lightColor", lightColor);

    figure.render();

    shader2.use();

    model = glm::mat4(1.0f);
    const glm::mat3 normal = glm::transpose(glm::inverse(model));

    shader2.set("model", model);
    shader2.set("view", view);
    shader2.set("projection", projection);
    shader2.set("normal", normal);

    glm::vec3 viewLightPosition = glm::vec3(view * glm::vec4(lightPosition, 1.0f));
    shader2.set("light.position", viewLightPosition);
    shader2.set("light.ambient", lightColor * glm::vec3(0.1f));
    shader2.set("light.diffuse", lightColor * glm::vec3(0.8f));
    shader2.set("light.specular", lightColor * glm::vec3(0.5f, 0.5f, 0.5f));

    /*
     * Establecer en shader de phong los valores de la linterna:
     *  > Posición
     *  > Dirección
     *  > Ángulos de corte (cutOff y outerCutOff)
     *  > Componentes ambiente, difusa y especular
    */
    shader2.set("flashLight.position", glm::vec3(view * glm::vec4(flashPosition, 1.0f)));
    shader2.set("flashLight.direction", glm::normalize(glm::mat3(view) * flashDirection));
    shader2.set("flashLight.cutOff", glm::cos(glm::radians(12.52f)));
    shader2.set("flashLight.outerCutOff", glm::cos(glm::radians(17.5f)));
    shader2.set("flashLight.ambient", flashColor * glm::vec3(0.05f));
    shader2.set("flashLight.diffuse", flashColor * glm::vec3(0.8f));
    shader2.set("flashLight.specular", flashColor * glm::vec3(1.0f));

    shader2.set("material.ambient", objectColor);
    shader2.set("material.diffuse", objectColor);
    shader2.set("material.specular", objectColor);
    shader2.set("material.shininess", 1);

    glm::vec3 viewCameraPosition = glm::vec3(view * glm::vec4(camera.getPosition(), 1.0f));
    shader2.set("cameraPosition", viewCameraPosition);

    figure.render();
}

int main(int, char*[]) 
{
    system("chcp 65001");

    Window* window = Window::instance();
    Input* input = Input::instance();

    input->setMouseMoveCallback(onMouseMove);
    input->setScrollMoveCallback(onScrollMove);

    const Sphere figure(1.0f, 50, 50);

    const Shader lightShader(PROJECT_PATH "light.vert", PROJECT_PATH "light.frag");
    const Shader phongShader(PROJECT_PATH "phong.vert", PROJECT_PATH "phong.frag");

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
        render(lightShader, phongShader, figure);
        window->frame();
    }

    return 0;
}