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

#include <iostream>

std::vector<glm::vec3> cubePositions
{
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 6.0f, -20.0f),
    glm::vec3(-2.0f, -2.0f, -2.0f),
    glm::vec3(-4.0f, -6.0f, -10.0f),
    glm::vec3(3.0f, -1.0f, -4.0f),
    glm::vec3(-2.0f, 3.0f, -8.0f),
    glm::vec3(2.0f, -2.0f, -3.0f),
    glm::vec3(1.0f, 2.0f, -2.0f),
    glm::vec3(1.0f, 0.0f, -2.0f),
    glm::vec3(-1.0f, 1.0f, -1.0f)
};

// Fijar cámara en una posición
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

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

    // Manejar movimiento del ratón
    camera.handleMouseMovement(offsetX, offsetY);
}

void onScrollMove(const float offsetX, const float offsetY)
{
    // Manejar desplazamiento del ratón
    camera.handleMouseScroll(offsetY);
}

void handleInput(const float time)
{
    Input* input = Input::instance();

    // Manejar teclas presionadas del teclado
    if(input->isKeyPressed(GLFW_KEY_W))
    {
        // Movimiento de la cámara hacia adelante
        camera.handleKeyboard(Camera::Movement::Forward, time);
    }
    if(input->isKeyPressed(GLFW_KEY_S))
    {
        // Movimiento de la cámara hacia atrás
        camera.handleKeyboard(Camera::Movement::Backward, time);
    }
    if(input->isKeyPressed(GLFW_KEY_D))
    {
        // Movimiento de la cámara hacia la izquierda
        camera.handleKeyboard(Camera::Movement::Left, time);
    }
    if(input->isKeyPressed(GLFW_KEY_A))
    {
        // Movimiento de la cámara hacia la derecha
        camera.handleKeyboard(Camera::Movement::Right, time);
    }
}

void render(const Shader shader, const Geometry& figure, const Texture& texture1, const Texture& texture2)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    // Obtener matriz de vista desde la cámara
    glm::mat4 view = camera.getViewMatrix();

    Window* window = Window::instance();

    // Obtener matriz de proyección desde el FOV de la cámara
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

    shader.set("view", view);
    shader.set("projection", projection);

    texture1.use(shader, "texture1", 0);
    texture2.use(shader, "texture2", 1);

    for(size_t i = 0; i < cubePositions.size(); ++i)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(10.0f + (20.0f * static_cast<float>(i))), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.set("model", model);
        figure.render();
    }

}

int main(int, char*[]) 
{
    system("chcp 65001");

    Window* window = Window::instance();
    Input* input = Input::instance();

    input->setMouseMoveCallback(onMouseMove);
    input->setScrollMoveCallback(onScrollMove);

    const Cube figure(1.0f);
    const Shader shader(PROJECT_PATH "camera.vert", PROJECT_PATH "camera.frag");
    const Texture texture1(ASSETS_PATH "textures/bricks_arrow.jpg", Texture::Format::RGB);
    const Texture texture2(ASSETS_PATH "textures/blue_blocks.jpg", Texture::Format::RGB);

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
        render(shader, figure, texture1, texture2);
        window->frame();
    }

    return 0;
}