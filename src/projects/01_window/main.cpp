#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void onChangeFrameBufferSize(GLFWwindow* window, int width, int height)
{
    // Cambiar Viewport
    glViewport(0, 0, width, height);
    std::cout << "Nuevo tamaño de ventana: " << width << "x" << height << std::endl;
}

void handleInput(GLFWwindow* window)
{
    // Cerrar ventana si se presiona la tecla Esc
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void render()
{
    // Borrar buffer de color
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int, char*[]) 
{
    // Permitir el encoding español
    system("chcp 65001");

    // Sección de variables
    GLFWwindow* window;
    int width, height;

    // Inicializar GLFW
    if(!glfwInit())
    {
        std::cout << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    // Darle hints -pistas- a GLFW sobre los contextos que queremos
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Crear la ventana
    window = glfwCreateWindow(800, 600, "60GIIN_10_A_2024_25", nullptr, nullptr);
    if(!window)
    {
        std::cout << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Generar contexto actual de la ventama
    glfwMakeContextCurrent(window);

    // Inicializar glad
    if(!gladLoadGL())
    {
        std::cout << "Error al inicializar glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Redimensionar la ventana
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, onChangeFrameBufferSize);

    // Obtener color de fondo de la ventana
    glClearColor(0.0f, 0.2f, 0.5f, 1.0f);

    /* 
    ** Ejecución hasta que:
    **  > cierre la ventana
    **  > pulse la tecla Esc
    */
    while(!glfwWindowShouldClose(window))
    {
        // Manejar eventos de entrada
        handleInput(window);

        // Actualizar estado
        //update();

        // Renderizar
        render();

        //Intercambiar buffers
        glfwSwapBuffers(window);

        // Consultar nuevos eventos
        glfwPollEvents();
    }

    // Liberar GLFW
    glfwTerminate();

    return 0;
}