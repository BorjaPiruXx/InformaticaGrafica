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

std::pair<uint32_t, uint32_t> createFBO() {
  uint32_t fbo;
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  uint32_t textureColor;
  glGenTextures(1, &textureColor);
  glBindTexture(GL_TEXTURE_2D, textureColor);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::instance()->getWidth(), Window::instance()->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColor, 0);

  uint32_t rbo;
  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::instance()->getWidth(), Window::instance()->getHeight());
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Error Framebuffer not complete" << std::endl;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return std::make_pair(fbo, textureColor);
}

void render(const Geometry& quad, const Geometry& cube, const Shader& phong_shader, const Shader& fbo_shader,
  const Texture& t_albedo, const Texture& t_specular, const uint32_t fbo, const uint32_t text_fbo) {

  glm::vec3 lightPos = glm::vec3(3.0f, 1.0f, 0.0f);
  glm::vec3 lightColor = glm::vec3(1.0f, 0.0f, 0.0f);

  glm::mat4 view = camera.getViewMatrix();
  Window* window = Window::instance();
  const glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()),
    static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

  {  //FIRST PASS - USE MY FBO, OFFLINE RENDER
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    phong_shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

    glm::mat3 normalMat = glm::transpose(glm::inverse(model));

    phong_shader.set("model", model);
    phong_shader.set("view", view);
    phong_shader.set("proj", proj);
    phong_shader.set("normalMat", normalMat);

    phong_shader.set("light.position", lightPos);
    phong_shader.set("light.ambient", lightColor * glm::vec3(0.1f));
    phong_shader.set("light.diffuse", lightColor * glm::vec3(0.8f));
    phong_shader.set("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    t_albedo.use(phong_shader, "material.diffuse", 0);
    t_specular.use(phong_shader, "material.specular", 1);
    phong_shader.set("material.shininess", 32);

    phong_shader.set("viewPos", camera.getPosition());

    quad.render();

    model = glm::mat4(1.0f);
    phong_shader.set("model", model);
    normalMat = glm::transpose(glm::inverse(model));
    phong_shader.set("normalMat", normalMat);

    cube.render();
  }
  
  {  //SECOND PASS - RENDER TO SCREEN
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT);

    fbo_shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, text_fbo);
    fbo_shader.set("screen_texture", 0);

    quad.render();
  }
}

int main(int, char* []) {

  system("chcp 65001");
  
  Window* window = Window::instance();
  Input* input = Input::instance();

  input->setMouseMoveCallback(onMouseMove);
  input->setScrollMoveCallback(onScrollMove);

  const Texture t_albedo(ASSETS_PATH "textures/bricks_albedo.png", Texture::Format::RGB);
  const Texture t_specular(ASSETS_PATH "textures/bricks_specular.png", Texture::Format::RGB);
  const Quad quad(2.0f);
  const Cube cube(1.0f);
  const Shader fbo_shader(PROJECT_PATH "fbo.vert", PROJECT_PATH "fbo.frag");
  const Shader phong_shader(PROJECT_PATH "phong.vert", PROJECT_PATH "phong.frag");

  auto fbo = createFBO();

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
    render(quad, cube, phong_shader, fbo_shader, t_albedo, t_specular, fbo.first, fbo.second);
    window->frame();
  }

  return 0;
}