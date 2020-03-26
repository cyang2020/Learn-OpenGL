#include "Camera.hpp"
Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp) {
    Position = position;
    WorldUp = worldUp;
    Direction = glm::normalize(direction - position);
    Right = glm::normalize(glm::cross(Direction, WorldUp));
    Up = glm::normalize(glm::cross(Direction, Right));
}
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp) {
    Position = position;
    WorldUp = worldUp;
    Pitch = pitch;
    Yaw = yaw;
    glm::vec3 front;
    front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
    front.y = sin(glm::radians(Pitch));
    front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
    Direction = glm::normalize(front);
    Right = glm::normalize(glm::cross(Direction, WorldUp));
    Up = glm::normalize(glm::cross(Right, Direction));
}
void Camera::processMouseMovement(float deltaX, float deltaY) {
    Pitch += deltaY;
    Yaw += deltaX;
    updateCameraVector();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Direction, WorldUp);
}
void Camera::updateCameraVector() {
    glm::vec3 front;
    front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
    front.y = sin(glm::radians(Pitch));
    front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
    Direction = glm::normalize(front);
    Right = glm::normalize(glm::cross(Direction, WorldUp));
    Up = glm::normalize(glm::cross(Right, Direction));
}


