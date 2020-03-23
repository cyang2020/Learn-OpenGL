#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera{
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
    glm::vec3 Position;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;
    glm::mat4 getViewMatrix();
};
#endif /* Camera_hpp */
