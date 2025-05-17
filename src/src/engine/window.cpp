#include "engine/window.hpp"
#include "engine/input.hpp"

#pragma warning(push, 0)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma warning(pop)

#include <iostream>

void onChangeFrameBufferSize(GLFWwindow*, const int32_t width, const int32_t height) noexcept 
{
    Window::instance()->setWidth(static_cast<uint32_t>(width));
    Window::instance()->setHeight(static_cast<uint32_t>(height));
    glViewport(0, 0, width, height);
    std::cout << "Nuevo tamaño de ventana: " << width << "x" << height << std::endl;
}

void onKeyPressed(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) 
{

    if((action == GLFW_PRESS) && (key == GLFW_KEY_ESCAPE)) 
    {
        glfwSetWindowShouldClose(window, true);
    } else 
    {
        Input::instance()->keyPressed(key, action);
    }
}

void onMouse(GLFWwindow* /*window*/, double xpos, double ypos) 
{
    Input::instance()->mouseMoved(static_cast<float>(xpos), static_cast<float>(ypos));
}

void onScroll(GLFWwindow* /*window*/, double xoffset, double yoffset) 
{
    Input::instance()->scrollMoved(static_cast<float>(xoffset), static_cast<float>(yoffset));
}

Window* Window::instance() 
{
    static Window w;
    return &w;
}

Window::Window() 
{
    if(!glfwInit()) 
    {
        std::cout << "Error al inicializar GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(static_cast<int>(_width), static_cast<int>(_height), "60GIIN_10_A_2024_25", nullptr, nullptr);
    if(!_window) 
    {
        std::cout << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(_window);

    glfwSetFramebufferSizeCallback(_window, onChangeFrameBufferSize);

    glfwSetKeyCallback(_window, onKeyPressed);
    glfwSetCursorPosCallback(_window, onMouse);
    glfwSetScrollCallback(_window, onScroll);

    if (!gladLoadGL()) 
    {
        std::cout << "Error al inicializar glad" << std::endl;
        exit(-1);
    }

    setCaptureMouse(true);
}

Window::~Window() 
{
    glfwTerminate();
}

bool Window::isAlive() const 
{
    return !glfwWindowShouldClose(_window);
}

void Window::frame() const 
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

bool Window::isKeyPressed(int key) 
{
    return glfwGetKey(Window::instance()->getNativeWindow(), key) == GLFW_PRESS;
}

void Window::setCaptureMouse(bool toggle) const 
{
    if(toggle) 
    {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else 
    {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}