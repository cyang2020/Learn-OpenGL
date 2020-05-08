//
//  SpotLight.hpp
//  OpenGL
//
//  Created by Casper Yang on 5/7/20.
//  Copyright © 2020 Casper Yang. All rights reserved.
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"

class SpotLight{
public:
    Shader* shader;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 position;
    glm::vec3 direction;
    float cutoff;
    float cutoffOuter;
    
    SpotLight(Shader* _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _position, glm::vec3 _direction, float _cutoff, float _cutoffOuter);
    void setUniforms();
};
#endif /* SpotLight_hpp */
