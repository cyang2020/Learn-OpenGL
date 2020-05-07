#include "PointLight.hpp"
PointLight::PointLight(Shader* _shader, glm::vec3 _position, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _constant, float _linear, float _quadratic){
    shader = _shader;
    position = _position;
    ambient = _ambient;
    diffuse = _diffuse;
    specular = _specular;
    constant = _constant;
    linear = _linear;
    quadratic = _quadratic;
}
void PointLight::setUniforms(){
    shader->setVec3Uni("pointLight.position", position);
    shader->setVec3Uni("pointLight.ambient", ambient);
    shader->setVec3Uni("pointLight.diffuse", diffuse);
    shader->setVec3Uni("pointLight.specular", specular);
    
    shader->setFloatUni("pointLight.constant", constant);
    shader->setFloatUni("pointLight.linear", linear);
    shader->setFloatUni("pointLight.quadratic", quadratic);
}
