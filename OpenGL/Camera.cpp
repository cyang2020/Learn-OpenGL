#include "Camera.hpp"
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp){
    Position = position;
    WorldUp = worldUp;
    Forward = glm::normalize(target - position);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right));
}
glm::mat4 Camera::getViewMatrix(){
    return glm::lookAt(Position, Position + Forward, WorldUp);
}

