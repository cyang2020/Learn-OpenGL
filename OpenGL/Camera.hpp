#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);
    Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);
    glm::vec3 Position;
    glm::vec3 Direction;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;
    float Pitch;
    float Yaw;
    glm::mat4 getViewMatrix();
    void processMouseMovement(float deltaX, float deltaY);
private:
    void updateCameraVector();
};
#endif /* Camera_hpp */
