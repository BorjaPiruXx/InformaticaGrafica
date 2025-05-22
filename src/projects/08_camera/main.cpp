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
#include <engine/geometry/cube.hpp>
#include <engine/geometry/sphere.hpp>

#include <iostream>

// Sección variables estáticas
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

/*
 * Vectores necesarios para movimiento de la cámara:
 *  > posición de la cámara
 *  > punto al que mira la cámara
 *  > vector normal de la cámara
 *  > movimiento de la cámara
 *
*/
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

// Velocidad de movimiento de la cámara
const float cameraSpeed = 1.5f;

// Últimas posiciones del ratón conocidas en ejes X e Y
bool firstMouse = true;
float lastMouseX, lastMouseY;

// Posición inicial de los giros Pitch y Yaw
float pitch = 0.0f;
float yaw = -90.0f;

float fov = 45.0f;
const float near = 0.1f;
const float far = 100.0f;

void onMouseMove(const float x, const float y)
{
    // Comprobar si es la primera vez que se utiliza el ratón
    if(firstMouse)
    {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }

    // Posición actual del ratón
    float offsetX = x - lastMouseX;
    float offsetY = lastMouseY - y;
    lastMouseX = x;
    lastMouseY = y;

    // Limitar la sensibilidad del movimiento de la cámara
    float sensitivity = 0.1f;
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    // Posición actual de los giros Pitch y Yaw
    pitch += offsetY;
    yaw += offsetX;

    // Impedir que el Pitch supere cierto ángulo de giro
    pitch = pitch > 80.0f ? 80.0f : pitch;
    pitch = pitch < -80.0f ? -80.0f : pitch;

    // Obtener la dirección de la cámara con respecto al Pitch y Yaw
    glm::vec3 direction = glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
    cameraFront = glm::normalize(direction);
}

void onScrollMove(const float offsetX, const float offsetY)
{
    // Disminuir el fov según el offset del eje Y, al estar en el intervalo idóneo
    fov -= offsetY;
    fov = fov < 10.0f ? 10.0f : fov;
    fov = fov > 45.0f ? 45.0f : fov;

}

void handleInput(const float time)
{
    // Obtener velocidad de escalado en función del tiempo
    const float speed = cameraSpeed * time;

    // Comprobar si se ha pulsado alguna tecla
    Input* input = Input::instance();

    // Si la tecla es W, la cámara se acerca
    if(input->isKeyPressed(GLFW_KEY_W))
    {
        cameraPosition += speed * cameraFront;
    }

    // Si la tecla es S, la cámara se aleja
    if(input->isKeyPressed(GLFW_KEY_S))
    {
        cameraPosition -= speed * cameraFront;
    }

    // Si la tecla es D, la cámara se mueve hacia la derecha
    if(input->isKeyPressed(GLFW_KEY_D))
    {
        cameraPosition += speed * cameraRight;
    }

    // Si la tecla es A, la cámara se mueve hacia la izquierda
    if(input->isKeyPressed(GLFW_KEY_A))
    {
        cameraPosition -= speed * cameraRight;
    }

}

void render(const Shader shader, const Geometry& figure, const Texture& texture1, const Texture& texture2)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    // Generar matriz de vista de la cámara
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

    Window* window = Window::instance();
    glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

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

    // Controlar el movimiento del ratón
    Input* input = Input::instance();
    input->setMouseMoveCallback(onMouseMove);

    // Controlar el zoom con la ruleta del ratón
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

    // Tiempo inicial del programa
    float lastFrame = 0.0f;

    while(window->isAlive())
    {
        // Tiempo actual del frame
        const auto currentFrame = static_cast<float>(glfwGetTime());

        // Tiempo entre el último frame y el actual
        const float deltaTime = currentFrame - lastFrame;

        // Actualizar tiempo del último frame
        lastFrame = currentFrame;

        handleInput(deltaTime);
        //update();
        render(shader, figure, texture1, texture2);
        window->frame();
    }

    return 0;
}