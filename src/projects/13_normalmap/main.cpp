#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "stb_image.h"
#include "engine/input.hpp"

#include "engine/window.hpp"
#include "engine/shader.hpp"
#include "engine/texture.hpp"
#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/geometry/quad.hpp"
#include "engine/geometry/sphere.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

bool firstMouse = true;
float lastX, lastY;
float yaw = -90.0f;
float pitch = 0.0f;

const float near = 0.1f;
const float far = 100.0f;

void onMouseMove(float x, float y) {
  if (firstMouse) {
    lastX = x;
    lastY = y;
    firstMouse = false;
  }

  float xoffset = x - lastX;
  float yoffset = lastY - y;
  lastX = x;
  lastY = y;

  camera.handleMouseMovement(xoffset, yoffset);
}

void onScrollMove(float xOffset, float yOffset) {
  camera.handleMouseScroll(yOffset);
}

void handleInput(float deltaTime) {
  Input* input = Input::instance();

  if (input->isKeyPressed(GLFW_KEY_W))
    camera.handleKeyboard(Camera::Movement::Forward, deltaTime);
  if (input->isKeyPressed(GLFW_KEY_S))
    camera.handleKeyboard(Camera::Movement::Backward, deltaTime);
  if (input->isKeyPressed(GLFW_KEY_A))
    camera.handleKeyboard(Camera::Movement::Left, deltaTime);
  if (input->isKeyPressed(GLFW_KEY_D))
    camera.handleKeyboard(Camera::Movement::Right, deltaTime);
}

void render(const Geometry& quad, const Geometry& sphere, const Shader& light_shader, const Shader& phong_shader, const Shader& normal_shader,
  const Texture& t_albedo, const Texture& t_specular, const Texture& t_normal) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

  glm::mat4 view = camera.getViewMatrix();
  Window* window = Window::instance();
  const glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()),
    static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

  float l_pos[] = { std::sin((float)glfwGetTime() / 2.0f), 0.0f, std::abs( std::cos((float)glfwGetTime() / 2.0f)) };
  glm::vec3 lightPos = glm::vec3(l_pos[0], l_pos[1], l_pos[2]);

  {
    light_shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.1f));

    light_shader.set("model", model);
    light_shader.set("view", view);
    light_shader.set("proj", proj);

    light_shader.set("lightColor", lightColor);

    sphere.render();
  }

  // ==============================================

  {
    phong_shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(model)));

    phong_shader.set("model", model);
    phong_shader.set("view", view);
    phong_shader.set("proj", proj);
    phong_shader.set("normalMat", normalMat);

    phong_shader.set("viewPos", camera.getPosition());

    t_albedo.use(phong_shader, "material.diffuse", 0);
    t_specular.use(phong_shader, "material.specular", 1);
    phong_shader.set("material.shininess", 16);

    phong_shader.set("light.position", lightPos);
    phong_shader.set("light.ambient", lightColor * glm::vec3(0.1f));
    phong_shader.set("light.diffuse", lightColor * glm::vec3(0.5f));
    phong_shader.set("light.specular", lightColor);

    quad.render();
  }

  {
    normal_shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
    glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(model)));

    normal_shader.set("model", model);
    normal_shader.set("view", view);
    normal_shader.set("proj", proj);
    normal_shader.set("normalMat", normalMat);

    normal_shader.set("viewPos", camera.getPosition());

    t_albedo.use(normal_shader, "material.diffuse", 0);
    t_specular.use(normal_shader, "material.specular", 1);
    t_normal.use(normal_shader, "material.normal", 2);
    normal_shader.set("material.shininess", 16);

    normal_shader.set("light.position", lightPos);
    normal_shader.set("light.ambient", lightColor * glm::vec3(0.1f));
    normal_shader.set("light.diffuse", lightColor * glm::vec3(0.5f));
    normal_shader.set("light.specular", lightColor);

    quad.render();
  }

}

int main(int, char* []) {

  system("chcp 65001");
  
  Window* window = Window::instance();
  Input* input = Input::instance();

  input->setMouseMoveCallback(onMouseMove);
  input->setScrollMoveCallback(onScrollMove);

  const Quad quad(2.0f, true);
  const Sphere sphere(0.25f, 10, 10);
  const Shader light_shader(PROJECT_PATH "light.vert", PROJECT_PATH "light.frag");
  const Shader phong_shader(PROJECT_PATH "phong.vert", PROJECT_PATH "phong.frag");
  const Shader normal_shader(PROJECT_PATH "normal.vert", PROJECT_PATH "normal.frag");
  const Texture t_albedo(ASSETS_PATH "textures/bricks_albedo.png", Texture::Format::RGB);
  const Texture t_specular(ASSETS_PATH "textures/bricks_specular.png", Texture::Format::RGB);
  const Texture t_normal(ASSETS_PATH "textures/bricks_normal.png", Texture::Format::RGB);

  glClearColor(0.0f, 0.2f, 0.5f, 1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

  float lastFrame = 0.0f;

  while (window->isAlive()) {
    const auto currentFrame = static_cast<float>(glfwGetTime());
    const float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    handleInput(deltaTime);
    //update();
    render(quad, sphere, light_shader, phong_shader, normal_shader, t_albedo, t_specular, t_normal);
    window->frame();
  }

  return 0;
}