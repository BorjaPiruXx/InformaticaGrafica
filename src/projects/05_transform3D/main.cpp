#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

#include <engine/window.hpp>
#include <engine/shader.hpp>

#include <iostream>

void handleInput()
{
    
}

GLenum getTextureEnum(int i)
{
    switch(i)
    {
        case 1:
            return GL_TEXTURE1;
        case 2:
            return GL_TEXTURE2;
        case 3:
            return GL_TEXTURE3;
        case 4:
            return GL_TEXTURE4;
        case 5:
            return GL_TEXTURE5;
        case 6:
            return GL_TEXTURE6;
        case 7:
            return GL_TEXTURE7;
        case 8:
            return GL_TEXTURE8;
        case 9:
            return GL_TEXTURE9;
        case 10:
            return GL_TEXTURE10;
        case 11:
            return GL_TEXTURE11;
        case 12:
            return GL_TEXTURE12;
        case 13:
            return GL_TEXTURE13;
        case 14:
            return GL_TEXTURE14;
        case 15:
            return GL_TEXTURE15;
        case 16:
            return GL_TEXTURE16;
        case 17:
            return GL_TEXTURE17;
        case 18:
            return GL_TEXTURE18;
        case 19:
            return GL_TEXTURE19;
        case 20:
            return GL_TEXTURE20;
        case 21:
            return GL_TEXTURE21;
        case 22:
            return GL_TEXTURE22;
        case 23:
            return GL_TEXTURE23;
        case 24:
            return GL_TEXTURE24;
        case 25:
            return GL_TEXTURE25;
        case 26:
            return GL_TEXTURE26;
        case 27:
            return GL_TEXTURE27;
        case 28:
            return GL_TEXTURE28;
        case 29:
            return GL_TEXTURE29;
        case 30:
            return GL_TEXTURE30;
        case 31:
            return GL_TEXTURE31;
        default:
            return GL_TEXTURE0;
    }
}

char* getTextureName(int i)
{
    std::string name = "texture" + std::to_string(i);
    char* texture = new char[50];
    std::copy(name.begin(), name.end(), texture);
    texture[name.size()] = '\0';
    return texture;
}

void addTexturesOnShader(const Shader shader, uint32_t* textures)
{
    size_t size = sizeof(textures) / sizeof(textures[0]);
    for(int i = 0; i < size; ++i)
    {
        glActiveTexture(getTextureEnum(i));
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        shader.set(getTextureName(i + 1), i);
    }
}

void render(const Shader shader, uint32_t vao, uint32_t* textures)
{
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();

    // Crear matriz de transformación
    glm::mat4 matrix = glm::mat4(1.0f);

    // Trasladar matriz hacia la derecha (eje X)
    matrix = glm::translate(matrix, glm::vec3(0.2f, 0.0f, 0.0f));

    /*
     * Rotar matriz:
     *  > ciertos grados sobre alguno de los ejes
     *  > de manera continuada (movimiento del objeto)
    */
    //matrix = glm::rotate(matrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::rotate(matrix, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

    // Escalar matriz a la mitad en los 3 ejes (uniforme)
    matrix = glm::scale(matrix, glm::vec3(0.5f, 0.5f, 0.5f));

    // Establecer en el shader el valor de la matriz
    shader.set("transform", matrix);

    glBindVertexArray(vao);
    addTexturesOnShader(shader, textures);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

std::tuple<uint32_t, uint32_t, uint32_t> createVertexData() 
{
    float vertex[] = 
    {
       //   Posiciones              Colores             Coordenadas de textura
       0.5f, 0.5f, 0.0f,        1.0f, 0.0f, 0.0f,           1.0f, 1.0f,
       0.5f, -0.5f, 0.0f,       0.0f, 1.0f, 0.0f,           1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,           0.0f, 0.0f,
       -0.5f, 0.5f, 0.0f,       1.0f, 1.0f, 0.0f,           0.0f, 1.0f
    };

    uint32_t index[] = 
    {
        0, 3, 1,
        1, 3, 2
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return std::make_tuple(vao, vbo, ebo);
}

uint32_t createTexture(const char* path)
{
    uint32_t texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    unsigned char* image = stbi_load(path, &width, &height, &channels, 0);
    if(!image)
    { 
        std::cout << "Error al cargar textura: " << path << std::endl;
        exit(-1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    std::string strPath(path);
    std::cout << "Tamaño de textura \"" << strPath.substr(strPath.find_last_of("/") + 1) << "\": " << width << "x" << height << std::endl;
    stbi_image_free(image);

    return texture;
}

int main(int, char*[]) 
{
    system("chcp 65001");

    Window* window = Window::instance();
    std::tuple<uint32_t, uint32_t, uint32_t> vertex = createVertexData();
    const Shader shader(PROJECT_PATH "transform3D.vert", PROJECT_PATH "transform3D.frag");

    // Generar array de texturas de una imagen y darle la vuelta verticalmente
    stbi_set_flip_vertically_on_load(true);
    uint32_t* textures = new uint32_t[2] {
        createTexture(ASSETS_PATH "textures/bricks_arrow.jpg"),
        createTexture(ASSETS_PATH "textures/blue_blocks.jpg")
    };

    glClearColor(0.0f, 0.2f, 0.5f, 1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(window->isAlive())
    {
        handleInput();
        //update();
        render(shader, std::get<0>(vertex), textures);
        window->frame();
    }

    glDeleteBuffers(1, &std::get<2>(vertex));
    glDeleteBuffers(1, &std::get<1>(vertex));
    glDeleteVertexArrays(1, &std::get<0>(vertex));

    return 0;
}