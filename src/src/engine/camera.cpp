#include "engine/camera.hpp"

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch) 
{
  position_ = position;
  worldUp_ = up;
  yaw_ = yaw;
  pitch_ = pitch;
  fov_ = k_FOV;
  updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
{
  position_ = glm::vec3(posX, posY, posZ);
  worldUp_ = glm::vec3(upX, upY, upZ);
  yaw_ = yaw;
  pitch_ = pitch;
  fov_ = k_FOV;
  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const 
{
  return glm::lookAt(position_, position_ + front_, up_);
}

// Reemplazar el método lookAt de GLM por una implementación propia
glm::mat4 Camera::getViewMatrixWithoutGLM() const 
{
  // Definir eje Z (hacia atrás)
  glm::vec3 axisZ = glm::normalize(position_ - (position_ + front_));

  // Definir eje X (hacia la derecha)
  glm::vec3 axisX = glm::normalize(glm::cross(glm::normalize(up_), axisZ));

  // Definir eje Y (hacia arriba)
  glm::vec3 axisY = glm::cross(axisZ, axisX);

  // Generar matriz de vista (lookAt)
  glm::mat4 lookAt(1.0f);

  lookAt[0][0] = axisX.x;
  lookAt[1][0] = axisX.y;
  lookAt[2][0] = axisX.z;
  lookAt[3][0] = -glm::dot(axisX, position_);

  lookAt[0][1] = axisY.x;
  lookAt[1][1] = axisY.y;
  lookAt[2][1] = axisY.z;
  lookAt[3][1] = -glm::dot(axisY, position_);

  lookAt[0][2] = axisZ.x;
  lookAt[1][2] = axisZ.y;
  lookAt[2][2] = axisZ.z;
  lookAt[3][2] = -glm::dot(axisZ, position_);

  return lookAt;
}

float Camera::getFOV() const 
{
  return fov_;
}

glm::vec3 Camera::getPosition() const 
{
  return position_;
}

// Obtener el front de la cámara
glm::vec3 Camera::getFront() const
{
  return front_;
}

void Camera::updateCameraVectors() 
{
  glm::vec3 front;   // calculate the direction vector
  front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front.y = sin(glm::radians(pitch_));
  front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front_ = glm::normalize(front);

  right_ = glm::normalize(glm::cross(front_, worldUp_));
  up_ = glm::normalize(glm::cross(right_, front_));
}

void Camera::handleKeyboard(Movement direction, float dt) 
{
  const float velocity = k_Speed * dt;

  switch(direction) {
    case Movement::Forward:     position_ += front_ * velocity;  break;
    case Movement::Backward:    position_ -= front_ * velocity;  break;
    case Movement::Left:        position_ -= right_ * velocity;  break;
    case Movement::Right:       position_ += right_ * velocity;  break;
  }
}

void Camera::handleMouseMovement(float xoffset, float yoffset, bool constrainPitch) 
{
  float xoff = xoffset * k_Sensitivity;
  float yoff = yoffset * k_Sensitivity;

  yaw_ += xoff;
  pitch_ += yoff;

  if (constrainPitch) {
    if (pitch_> 89.0f) pitch_ = 89.0f;
    if (pitch_ < -89.0f) pitch_ = -89.0f;
  }

  updateCameraVectors();
}

void Camera::handleMouseScroll(float yoffset) 
{
  if (fov_ >= 1.0f && fov_ <= 45.0f) fov_ -= yoffset;
  if (fov_ <= 1.0f) fov_ = 1.0f;
  if (fov_ >= 45.0f) fov_ = 45.0f;
}