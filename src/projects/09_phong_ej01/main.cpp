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

/**
 * TODO:
 *  > Mover la luz alrededor del cubo describiendo un circulo sobre el eje Y
 *  > Cambiar valores de ambient, diffuse, specular y shininess y ver como se comporta el modelo de iluminación
 *  > Hacer el modelo de iluminación Phong en espacio de view, en lugar de en espacio de mundo
**/

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

void render(const glm::vec3& lightPosition, const Shader& shader1, const Shader& shader2, const Geometry& figure, const Texture& texture1, const Texture& texture2)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    Window* window = Window::instance();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

    glm::vec3 lightColor = glm::vec3(0.5f, 1.0f, 0.5f);
    glm::vec3 objectColor = glm::vec3(0.8f, 0.1f, 0.2f);

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

    // Transformar la posición de la luz al espacio de vista
    shader2.set("light.position", glm::vec3(view * glm::vec4(lightPosition, 1.0f)));

    shader2.set("light.ambient", lightColor * glm::vec3(0.1f));
    shader2.set("light.diffuse", lightColor * glm::vec3(0.8f));
    shader2.set("light.specular", lightColor * glm::vec3(0.5f, 0.5f, 0.5f));
    shader2.set("material.ambient", objectColor);
    shader2.set("material.diffuse", objectColor);
    shader2.set("material.specular", objectColor);
    shader2.set("material.shininess", 32);

    // Brillo metálico intenso
    /*shader2.set("light.ambient", lightColor * glm::vec3(0.05f));
    shader2.set("light.diffuse", lightColor * glm::vec3(0.6f));
    shader2.set("light.specular", lightColor * glm::vec3(0.2f));
    shader2.set("material.ambient", objectColor);
    shader2.set("material.diffuse", objectColor);
    shader2.set("material.specular", glm::vec3(1.0f));
    shader2.set("material.shininess", 64);*/

    // Superficie opáca - plástica 
    /*shader2.set("light.ambient", lightColor * glm::vec3(0.2f));
    shader2.set("light.diffuse", lightColor * glm::vec3(0.6f));
    shader2.set("light.specular", lightColor * glm::vec3(0.2f));
    shader2.set("material.ambient", objectColor);
    shader2.set("material.diffuse", objectColor);
    shader2.set("material.specular", glm::vec3(0.3f));
    shader2.set("material.shininess", 8);*/

    shader2.set("cameraPosition", camera.getPosition());

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

    const Shader shader1(PROJECT_PATH "light.vert", PROJECT_PATH "light.frag");
    const Shader shader2(PROJECT_PATH "phong.vert", PROJECT_PATH "phong.frag");

    const Texture texture1(ASSETS_PATH "textures/bricks_arrow.jpg", Texture::Format::RGB);
    const Texture texture2(ASSETS_PATH "textures/blue_blocks.jpg", Texture::Format::RGB);

    glClearColor(0.0f, 0.2f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float lastFrame = 0.0f;

    // Radio del círculo
    float lightRadius = 3.0f;

    while(window->isAlive())
    {
        const auto currentFrame = static_cast<float>(glfwGetTime());
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime);
        //update();

        // Declarar la posición de la luz como variable global
        float lightX = lightRadius * cos(currentFrame);
        float lightZ = lightRadius * sin(currentFrame);
        glm::vec3 lightPosition = glm::vec3(lightX, 1.0f, lightZ);

        render(lightPosition, shader1, shader2, figure, texture1, texture2);
        window->frame();
    }

    return 0;
}