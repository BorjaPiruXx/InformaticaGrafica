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

void renderBulb(const Shader& shader, const Geometry& figure, const glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.1f));

    shader.set("model", model);

    figure.render();
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

    // Obtener posición del foco
    glm::vec3 lightPosition = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 lightColor = glm::vec3(1.0f, 1.0, 1.0f);

    glm::mat4 view = camera.getViewMatrix();
    Window* window = Window::instance();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

    shader1.use();

    shader1.set("view", view);
    shader1.set("projection", projection);

    shader1.set("lightColor", lightColor);

    renderBulb(shader1, figure1, lightPosition);

    shader2.use();
    
    shader2.set("view", view);
    shader2.set("projection", projection);

    // Establecer en shader de phong los valores de la: posición del foco
    shader2.set("light.position", lightPosition);

    shader2.set("light.ambient", lightColor * glm::vec3(0.1f));
    shader2.set("light.diffuse", lightColor * glm::vec3(0.8f));
    shader2.set("light.specular", lightColor * glm::vec3(1.0f, 1.0f, 1.0f));

    /*
     * Establecer en shader de phong los valores de las componentes de la atenuación:
     *  > Constante
     *  > Lineal
     *  > Cuadrática
    */
    shader2.set("light.constant", 1.0f);
    shader2.set("light.lineal", 0.35f);
    shader2.set("light.quadratic", 0.44f);
    
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