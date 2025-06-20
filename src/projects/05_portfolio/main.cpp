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
#include <engine/geometry/quad.hpp>
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

std::pair<uint32_t, uint32_t> createFBO()
{
    uint32_t fbo, textureColor, rbo;

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &textureColor);
    glBindTexture(GL_TEXTURE_2D, textureColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::instance()->getWidth(), Window::instance()->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColor, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::instance()->getWidth(), Window::instance()->getHeight());
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
    {
        std::cout << "Error: Framebuffer incompleto" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return std::make_pair(fbo, textureColor);
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

    glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f, -1.0f, -0.3f));
    glm::vec3 lightPosition = glm::vec3(3.0f, 1.0f, 0.0f);
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

    object.render(shader2);
}

void renderBuffer(const Shader& shader1, const Shader& shader2, const Shader& shader3, const Geometry& figure1, const Geometry& figure2, 
    const Texture& texture1, const Texture& texture2, const Texture& texture3, const Model& object, std::pair<uint32_t, uint32_t> fbo)
{
    // Renderizar la escena al framebuffer
    {
        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo.first);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        render(shader1, shader2, figure1, texture1, texture2, texture3, object);
    }

    // Dibujar el contenido del framebuffer en el cuadrado
    {
        glDisable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader3.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fbo.second);
        shader3.set("screen", 0);

        figure2.render();
    }
}

int main(int, char*[]) 
{
    system("chcp 65001");

    Window* window = Window::instance();
    Input* input = Input::instance();

    input->setMouseMoveCallback(onMouseMove);
    input->setScrollMoveCallback(onScrollMove);

    const Sphere sphere(1.0f, 50, 50);

    // Cargar cuadrado en escena
    const Quad quad(1.0f);

    const Shader lightShader(PROJECT_PATH "light.vert", PROJECT_PATH "light.frag");
    const Shader phongShader(PROJECT_PATH "phong.vert", PROJECT_PATH "phong.frag");

    // Generar shader de escena
    const Shader screenShader(PROJECT_PATH "screen.vert", PROJECT_PATH "screen.frag");

    const Texture GB_D(ASSETS_PATH "models/Gun_Bot/GB_D.jpg", Texture::Format::RGB);
    const Texture GB_C(ASSETS_PATH "models/Gun_Bot/GB_C.jpg", Texture::Format::RGB);
    const Texture GB_N(ASSETS_PATH "models/Gun_Bot/GB_N.jpg", Texture::Format::RGB);

    const Model object(ASSETS_PATH "models/Gun_Bot/Gun_Bot.obj");

    // Generar frame buffer
    auto fbo = createFBO();

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

        // Renderizar la escena global del buffer
        renderBuffer(lightShader, phongShader, screenShader, sphere, quad, GB_D, GB_C, GB_N, object, fbo);
        
        window->frame();
    }

    return 0;
}