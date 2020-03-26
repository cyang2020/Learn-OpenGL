#include "Material.hpp"
Material::Material(Shader* _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess){
    shader = _shader;
    ambient = _ambient;
    diffuse = _diffuse;
    specular = _specular;
    shininess = _shininess;
}
void Material::setUniforms() {
    shader->setVec3Uni("material.ambient", ambient);
    shader->setVec3Uni("material.diffuse", diffuse);
    shader->setVec3Uni("material.specular", specular);
    shader->setFloatUni("material.shininess", shininess);
}
