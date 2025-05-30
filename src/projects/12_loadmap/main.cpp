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
#include "engine/model.hpp"
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

void render(const Shader& shader, const Model& object) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 view = camera.getViewMatrix();
  Window* window = Window::instance();
  const glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()),
    static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(0.20f));

  shader.use();

  shader.set("model", model);
  shader.set("view", view);
  shader.set("proj", proj);

  object.render(shader);
}

int main(int, char* []) {

  system("chcp 65001");

  Window* window = Window::instance();
  Input* input = Input::instance();

  input->setMouseMoveCallback(onMouseMove);
  input->setScrollMoveCallback(onScrollMove);

  const Shader shader(PROJECT_PATH "loadmap.vert", PROJECT_PATH "loadmap.frag");
  const Model object(ASSETS_PATH "models/Freighter/Freigther_BI_Export.obj");

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
    render(shader, object);
    window->frame();
  }

  return 0;
}