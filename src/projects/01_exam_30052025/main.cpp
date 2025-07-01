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

void setMatrixOnShader(glm::mat4& model, const glm::vec3 modelCoord, const glm::mat4 view, const glm::mat4 projection, const Shader& shader)
{
    model = glm::translate(glm::mat4(1.0f), modelCoord);
    shader.set("model", model);
    shader.set("view", view);
    shader.set("projection", projection);
}

void setLightOnShader(const glm::vec3 lightPosition, const glm::vec3 lightColor, const Shader& shader)
{
    shader.set("light.position", lightPosition);
    shader.set("light.ambient", lightColor * glm::vec3(0.025f));
    shader.set("light.diffuse", lightColor * glm::vec3(0.8f));
    shader.set("light.specular", lightColor * glm::vec3(1.0f, 1.0f, 1.0f));
}

void setTextureOnShader(bool useTextures, const Texture& texture, const Shader& shader)
{
    shader.set("useTextures", useTextures);
    if(useTextures)
    {
        texture.use(shader, "material.diffuse", 0);
        shader.set("material.specular", glm::vec3(0.8f, 0.4f, 0.2f));
    }
    shader.set("material.shininess", 32.0f);
}

void render(const Geometry& figure1, const Shader& shader1, 
    const Geometry& figure2, const Shader& shader2, 
    const Geometry& figure3, const Shader& shader3, const Texture& texture3_B, 
    const Geometry& figure4, const Shader& shader4, const Texture& texture4_B, const Texture& texture4_N)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    Window* window = Window::instance();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

    // Posición y color de la Point Light
    glm::vec3 lightPosition = glm::vec3(0.0f, 1.0f, 4.0f);
    glm::vec3 lightColor = glm::vec3(0.8f, 0.5f, 0.3f);

    glm::mat4 model = glm::mat4(1.0f);

    {
        shader1.use();
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.1f));
        shader1.set("model", model);
        shader1.set("view", view);
        shader1.set("projection", projection);
        shader1.set("lightColor", lightColor);
        figure1.render();
    }

    {
        shader2.use();
        setMatrixOnShader(model, glm::vec3(-3.0f, 0.0f, 0.0f), view, projection, shader2);
        setLightOnShader(lightPosition, lightColor, shader2);
        figure2.render();
    }

    {
        shader3.use();
        setMatrixOnShader(model, glm::vec3(0.0f, 0.0f, 0.0f), view, projection, shader3);
        setLightOnShader(lightPosition, lightColor, shader3);
        setTextureOnShader(true, texture3_B, shader3);
        figure3.render();
    }

    {
        shader4.use();
        setMatrixOnShader(model, glm::vec3(3.0f, 0.0f, 0.0f), view, projection, shader4);
        setLightOnShader(lightPosition, lightColor, shader4);
        shader4.set("cameraPosition", camera.getPosition());
        setTextureOnShader(true, texture4_B, shader4);
        shader3.set("normalMap", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture4_N.id());
        figure4.render();
    }

}

int main(int, char*[]) 
{
    system("chcp 65001");

    Window* window = Window::instance();
    Input* input = Input::instance();

    input->setMouseMoveCallback(onMouseMove);
    input->setScrollMoveCallback(onScrollMove);

    const Sphere light_sphere(1.0f, 50, 50);
    const Sphere flat_sphere(1.0f, 50, 50);
    const Sphere gouraud_sphere(1.0f, 50, 50);
    const Sphere phong_sphere(1.0f, 50, 50);

    const Shader light_shader(PROJECT_PATH "light.vert", PROJECT_PATH "light.frag");
    const Shader flat_shader(PROJECT_PATH "flat.vert", PROJECT_PATH "flat.frag");
    const Shader gouraud_shader(PROJECT_PATH "gouraud.vert", PROJECT_PATH "gouraud.frag");
    const Shader phong_shader(PROJECT_PATH "phong.vert", PROJECT_PATH "phong.frag");

    const Texture blue_blocks(ASSETS_PATH "textures/blue_blocks.jpg", Texture::Format::RGB);
    const Texture bricks_albedo(ASSETS_PATH "textures/bricks_albedo.png", Texture::Format::RGB);
    const Texture bricks_normal(ASSETS_PATH "textures/bricks_normal.png", Texture::Format::RGB);

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
        render(light_sphere, light_shader, flat_sphere, flat_shader, gouraud_sphere, gouraud_shader, blue_blocks, phong_sphere, phong_shader, bricks_albedo, bricks_normal);
        window->frame();
    }

    return 0;
}