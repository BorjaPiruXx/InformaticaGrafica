#include <engine/window.hpp>
#include <engine/shader.hpp>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

void handleInput()
{
    
}

void render(const Shader shader, uint32_t vao)
{
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

std::tuple<uint32_t, uint32_t, uint32_t> createVertexData() 
{
    float vertex[] = 
    {
       //   Posiciones              Colores
       0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
       0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f
    };

    uint32_t index[] = 
    {
        0, 2, 1
    };

    uint32_t vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return std::make_tuple(vao, vbo, ebo);
}

int main(int, char*[]) 
{
    system("chcp 65001");

    Window* window = Window::instance();
    std::tuple<uint32_t, uint32_t, uint32_t> vertex = createVertexData();

    // Construir el shader de vértices y fragmentos
    const Shader shader(PROJECT_PATH "color.vert", PROJECT_PATH "color.frag");

    glClearColor(0.0f, 0.2f, 0.5f, 1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(window->isAlive())
    {
        handleInput();
        //update();
        render(shader, std::get<0>(vertex));
        window->frame();
    }

    glDeleteBuffers(1, &std::get<2>(vertex));
    glDeleteBuffers(1, &std::get<1>(vertex));
    glDeleteVertexArrays(1, &std::get<0>(vertex));

    return 0;
}