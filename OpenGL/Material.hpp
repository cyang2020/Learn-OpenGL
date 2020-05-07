
#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"

class Material {
public:
    Shader *shader;
    unsigned int diffuseMap;
    unsigned int specularMap;
    float shininess;
    Material(Shader* _shader, unsigned int _diffuseMap, unsigned int _specularMap, float _shininess);
    void setUniforms();
};
#endif /* Material_hpp */
