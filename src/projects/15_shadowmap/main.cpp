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
glm::vec3 lightPos = glm::vec3(1.5f, 4.0f, 2.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

bool firstMouse = true;
float lastX, lastY;
float yaw = -90.0f;
float pitch = 0.0f;

const float near = 0.1f;
const float far = 100.0f;

const uint32_t k_shadow_width = 2048;
const uint32_t k_shadow_height = 2048;

const float k_shadow_near = 1.0f;
const float k_shadow_far = 7.5f;

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

  uint32_t depthMap;
  glGenTextures(1, &depthMap);
  glBindTexture(GL_TEXTURE_2D, depthMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, k_shadow_width, k_shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float borderColor[] = {1.0f, 1.0f, 1.0f};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glBindTexture(GL_TEXTURE_2D, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Error Framebuffer not complete" << std::endl;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return std::make_pair(fbo, depthMap);
}

void renderScene(const Shader& shader, const Geometry& quad, const Geometry& cube, const Geometry& sphere) {  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
  model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
  shader.set("model", model);
  glm::mat3 normalMat = glm::transpose(glm::inverse(model));
  shader.set("normalMat", normalMat);
  quad.render();

  model = glm::mat4(1.0f);
  shader.set("model", model);
  normalMat = glm::transpose(glm::inverse(model));
  shader.set("normalMat", normalMat);
  cube.render();

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(3.0f, 0.5f, 0.0f));
  shader.set("model", model);  
  normalMat = glm::transpose(glm::inverse(model));
  shader.set("normalMat", normalMat);
  cube.render();

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, 1.5f, 1.0f));
  model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
  shader.set("model", model);  
  normalMat = glm::transpose(glm::inverse(model));
  shader.set("normalMat", normalMat);
  sphere.render();

  model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(2.0f, 1.0f, -1.0f));
  model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
  shader.set("model", model);
  normalMat = glm::transpose(glm::inverse(model));
  shader.set("normalMat", normalMat);
  sphere.render();  
}

void configureShader(const Shader& shader, const Texture& t_albedo, const Texture& t_specular) {
  glm::mat4 view = camera.getViewMatrix();
  Window* window = Window::instance();
  const glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()),
    static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()), near, far);

  shader.use();
  shader.set("view", view);
  shader.set("proj", proj);

  shader.set("light.position", lightPos);
  shader.set("light.ambient", lightColor * glm::vec3(0.1f));
  shader.set("light.diffuse", lightColor * glm::vec3(0.8f));
  shader.set("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

  t_albedo.use(shader, "material.diffuse", 0);
  t_specular.use(shader, "material.specular", 1);
  shader.set("material.shininess", 32);

  shader.set("viewPos", camera.getPosition());
}

void render(const Geometry& quad, const Geometry& cube, const Geometry& sphere,
  const Shader& phong_shader, const Shader& debug_shader, const Shader& depth_shader, const Shader& light_shader,
  const Texture& t_albedo, const Texture& t_specular, 
  const uint32_t fbo, const uint32_t text_fbo) {

  Window* window = Window::instance();

  glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, k_shadow_near, k_shadow_far);
  glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 lightSpaceMatrix = lightProjection * lightView;

  { //FIRST PASS, CAMERA FROM THE LIGHT SOURCE   
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, k_shadow_width, k_shadow_height);   //1024 x 1024
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);

    depth_shader.use();
    depth_shader.set("lightSpaceMatrix", lightSpaceMatrix);

    renderScene(depth_shader, quad, cube, sphere);
  }

  //{ //DEBUG PASS, RENDER DEPTH BUFFER
  //  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //  glViewport(0, 0, static_cast<float>(window->getWidth()) , static_cast<float>(window->getHeight()));
  //  glClear(GL_COLOR_BUFFER_BIT);
  //  glDisable(GL_DEPTH_TEST);
  //  glCullFace(GL_BACK);

  //  debug_shader.use();
  //  glActiveTexture(GL_TEXTURE0);
  //  glBindTexture(GL_TEXTURE_2D, text_fbo);
  //  debug_shader.set("depth_map", 0);

  //  quad.render();
  //}

  { //SECOND PASS, RENDER SCENE USING DEPTH MAP
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, static_cast<float>(window->getWidth()) , static_cast<float>(window->getHeight()));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    configureShader(light_shader, t_albedo, t_specular);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    light_shader.set("model", model);
    sphere.render();

    configureShader(phong_shader, t_albedo, t_specular);

    phong_shader.set("lightSpaceMatrix", lightSpaceMatrix);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, text_fbo);
    phong_shader.set("depth_map", 2);

    renderScene(phong_shader, quad, cube, sphere);
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
  const Sphere sphere(1.0f, 20 ,20);
  const Shader debug_shader(PROJECT_PATH "debug.vert", PROJECT_PATH "debug.frag");
  const Shader phong_shader(PROJECT_PATH "phong.vert", PROJECT_PATH "phong.frag");
  const Shader depth_shader(PROJECT_PATH "depth.vert", PROJECT_PATH "depth.frag");
  const Shader light_shader(PROJECT_PATH "light.vert", PROJECT_PATH "light.frag");

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
    render(quad, cube, sphere, phong_shader, debug_shader, depth_shader, light_shader, t_albedo, t_specular, fbo.first, fbo.second);
    window->frame();
  }

  return 0;
}