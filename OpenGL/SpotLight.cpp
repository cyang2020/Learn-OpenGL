//
//  SpotLight.cpp
//  OpenGL
//
//  Created by Casper Yang on 5/7/20.
//  Copyright © 2020 Casper Yang. All rights reserved.
//

#include "SpotLight.hpp"

SpotLight::SpotLight(Shader* _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _position, glm::vec3 _direction, float _cutoff, float _cutoffOuter) {
    shader = _shader;
    position = _position;
    ambient = _ambient;
    diffuse = _diffuse;
    specular = _specular;
    direction = _direction;
    cutoff = _cutoff;
    cutoffOuter = _cutoffOuter;
}
void SpotLight::setUniforms(){
    shader->setVec3Uni("spotLight.position", position);
    shader->setVec3Uni("spotLight.ambient", ambient);
    shader->setVec3Uni("spotLight.diffuse", diffuse);
    shader->setVec3Uni("spotLight.specular", specular);
    shader->setVec3Uni("spotLight.direction", direction);
    shader->setFloatUni("spotLight.cutoff", cutoff);
    shader->setFloatUni("spotLight.cutoffOuter", cutoffOuter);
}
