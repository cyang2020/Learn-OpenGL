#include "Material.hpp"
Material::Material(Shader* _shader, unsigned int _diffuseMap, unsigned int _specularMap, float _shininess){
    shader = _shader;
//    ambient = _ambient;
//    diffuse = _diffuse;
    diffuseMap = _diffuseMap;
    specularMap = _specularMap;
    shininess = _shininess;
}
void Material::setUniforms() {
//    shader->setVec3Uni("material.ambient", ambient);
//    shader->setVec3Uni("material.diffuse", diffuse);
    shader -> setIntUni("material.diffuse", 0);
    shader -> setIntUni("material.specular", 1);
    shader -> setFloatUni("material.shininess", shininess);
}
