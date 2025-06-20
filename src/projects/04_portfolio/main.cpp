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
#include <engine/model.hpp>
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

void render(const Shader& shader1, const Shader& shader2, const Geometry& figure, const Texture& texture1, const Texture& texture2, const Texture& texture3, const Model& object)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrixWithoutGLM();
    Window* window = Window::instance();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

    // Dirección de la luz
    glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f, -1.0f, -0.3f));

    glm::vec3 lightPosition = glm::vec3(3.0f, 1.0f, 0.0f);

    // Color de la luz direccional
    glm::vec3 dirLightColor = glm::vec3(0.8f, 0.8f, 0.0f);

    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec3 flashPosition = camera.getPosition();
    glm::vec3 flashDirection = camera.getFront();
    glm::vec3 flashColor = glm::vec3(1.0f);

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

    /*
     * Establecer en shader de phong los valores de la luz direccional:
     *  > Dirección
     *  > Componentes ambiente, difusa y especular
    */
    shader2.set("dirLight.direction", glm::mat3(view) * lightDirection);
    shader2.set("dirLight.ambient", dirLightColor * glm::vec3(0.1f));
    shader2.set("dirLight.diffuse", dirLightColor * glm::vec3(0.8f));
    shader2.set("dirLight.specular", dirLightColor * glm::vec3(1.0f));

    shader2.set("light.position", lightPosition);
    shader2.set("light.ambient", lightColor * glm::vec3(0.1f));
    shader2.set("light.diffuse", lightColor * glm::vec3(0.8f));
    shader2.set("light.specular", lightColor * glm::vec3(0.5f, 0.5f, 0.5f));

    texture1.use(shader2, "material.diffuse", 0);
    texture2.use(shader2, "material.specular", 1);
    texture3.use(shader2, "material.normal", 2);
    shader2.set("material.shininess", 32.0f);

    shader2.set("cameraPosition", camera.getPosition());

    // Renderizar el objeto 3D
    object.render(shader2);
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

    // Cargar las texturas del modelo 3D
    const Texture GB_D(ASSETS_PATH "models/Gun_Bot/GB_D.jpg", Texture::Format::RGB);
    const Texture GB_C(ASSETS_PATH "models/Gun_Bot/GB_C.jpg", Texture::Format::RGB);
    const Texture GB_N(ASSETS_PATH "models/Gun_Bot/GB_N.jpg", Texture::Format::RGB);

    // Añadir modelo 3D
    const Model object(ASSETS_PATH "models/Gun_Bot/Gun_Bot.obj");

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
        render(lightShader, phongShader, figure, GB_D, GB_C, GB_N, object);
        window->frame();
    }

    return 0;
}