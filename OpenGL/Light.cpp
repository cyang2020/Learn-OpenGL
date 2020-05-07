#include "Light.hpp"

Light::Light(Shader* _shader, glm::vec3 _direction, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular){
    shader = _shader;
    direction = _direction;
    ambient = _ambient;
    diffuse = _diffuse;
    specular = _specular;
}
void Light::setUniforms(){
    shader->setVec3Uni("light.direction", direction);
    shader->setVec3Uni("light.ambient", ambient);
    shader->setVec3Uni("light.diffuse", diffuse);
    shader->setVec3Uni("light.specular", specular);
}
