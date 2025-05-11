#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

void onChangeFrameBufferSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    std::cout << "Nuevo tamaño de ventana: " << width << "x" << height << std::endl;
}

void handleInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void render(uint32_t program, uint32_t vao)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Usar el programa y ligar array de vértices
    glUseProgram(program);
    glBindVertexArray(vao);

    // Pintar elementos
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

std::tuple<uint32_t, uint32_t, uint32_t> createVertexData() 
{
    // Crear vértices
    float vertex[] = 
    {
        /*
         * Vértices de un triángulo
         * 0.5f, 0.5f, 0.0f,
         * 0.5f, -0.5f, 0.0f,
         * -0.5f, 0.5f, 0.0f
        */

       // Vértices de un cuadrado
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };

    // Relacionar vértices en elementos
    uint32_t index[] = 
    {
        0, 3, 1,
        3, 2, 1
    };

    // Generar array de vértices y buffers (vértices y elementos)
    uint32_t vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // Ligar comportamiento del array y de los buffers
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Subir información a los buffers
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    // Incluir atributos del vértice y habilitarlo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Desligar comportamiento de los buffers y el array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return std::make_tuple(vao, vbo, ebo);
}

bool checkShader(uint32_t shader)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        std::cout << "Error al compilar el shader: " << log << std::endl;
    }
    return success;
}

bool checkProgram(uint32_t program)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        char log[1024];
        glGetProgramInfoLog(program, 1024, nullptr, log);
        std::cout << "Error al compilar el programa: " << log << std::endl;
    }
    return success;
}

uint32_t createProgram()
{
    // Generar información del shader de vértices
    const char* vertexInfo = 
        "#version 330 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0"
    ;
    
    // Crear y verificar shader de vértices
    const uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexInfo, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader);

    // Generar información del shader de fragmentos
    const char* fragmentInfo =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.2, 0.7, 0.2, 1.0);\n"
        "}\0"
    ;

    // Crear y verificar shader de fragmentos
    const uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentInfo, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);

    // Crear programa e incluir ambos shaders compilados 
    const uint32_t program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Lincar y verificar programa
    glLinkProgram(program);
    checkProgram(program);

    // Limpiar de memoria CPU y GPU los shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

int main(int, char*[]) 
{
    system("chcp 65001");

    GLFWwindow* window;
    int width, height;
    uint32_t program;
    std::tuple<uint32_t, uint32_t, uint32_t> vertex;

    if(!glfwInit())
    {
        std::cout << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(800, 600, "60GIIN_10_A_2024_25", nullptr, nullptr);
    if(!window)
    {
        std::cout << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGL())
    {
        std::cout << "Error al inicializar glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, onChangeFrameBufferSize);

    glClearColor(0.0f, 0.2f, 0.5f, 1.0f);

    // Qué caras no deseo pintar (Culling)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /*
     * Cómo se pintan los póligonos (Wireframe)
     * glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    */

    // Obtener identificador del programa
    program = createProgram();

    // Obtener identificadores de los vértices
    vertex = createVertexData();

    while(!glfwWindowShouldClose(window))
    {
        handleInput(window);
        //update();
        render(program, std::get<0>(vertex));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Liberar buffers y array de vértices
    glDeleteBuffers(1, &std::get<2>(vertex));
    glDeleteBuffers(1, &std::get<1>(vertex));
    glDeleteVertexArrays(1, &std::get<0>(vertex));

    // Liberar programa
    glDeleteProgram(program);

    glfwTerminate();

    return 0;
}