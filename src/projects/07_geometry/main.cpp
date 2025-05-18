#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

#include <engine/window.hpp>
#include <engine/shader.hpp>
#include <engine/texture.hpp>
#include <engine/geometry/cube.hpp>
#include <engine/geometry/sphere.hpp>

#include <iostream>

// Generar vector estático con las posiciones de los cubos
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

void handleInput()
{
    
}

void render(const Shader shader, const Geometry& figure, const Texture& texture1, const Texture& texture2)
{
    // Limpiar además el buffer de profundidad
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    const float fov = 45.0f;
    const float near = 0.1f;
    const float far = 100.0f;
    Window* window = Window::instance();
    glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

    shader.set("view", view);
    shader.set("projection", projection);

    texture1.use(shader, "texture1", 0);
    texture2.use(shader, "texture2", 1);

    // Generar matriz de modelo para cada cubo
    for(size_t i = 0; i < cubePositions.size(); ++i)
    {
        glm::mat4 model = glm::mat4(1.0f);

        // Cada cubo se traslada a su respectiva posición
        model = glm::translate(model, cubePositions[i]);

        // Cada cubo rotará de manera diferente por el ángulo insertado
        model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(10.0f + (20.0f * static_cast<float>(i))), glm::vec3(0.5f, 1.0f, 0.0f));

        shader.set("model", model);
        figure.render();
    }

}

int main(int, char*[]) 
{
    system("chcp 65001");

    Window* window = Window::instance();

    /*
     * Crear una figura geométrica:
     *  > Cubo
     *  > Esfera
    */
    const Cube figure(1.0f);
    //const Sphere figure(0.5f, 30, 30);

    const Shader shader(PROJECT_PATH "geometry.vert", PROJECT_PATH "geometry.frag");
    
    // Crear texturas
    const Texture texture1(ASSETS_PATH "textures/bricks_arrow.jpg", Texture::Format::RGB);
    const Texture texture2(ASSETS_PATH "textures/blue_blocks.jpg", Texture::Format::RGB);

    glClearColor(0.0f, 0.2f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(window->isAlive())
    {
        handleInput();
        //update();
        render(shader, figure, texture1, texture2);
        window->frame();
    }

    return 0;
}