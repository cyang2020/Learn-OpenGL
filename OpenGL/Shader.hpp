#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    std::string vertexCode;
    std::string fragmentCode;
    const char* vertexShaderCode;
    const char* fragmentShaderCode;
    unsigned int ID;
    void use();
    void setBoolUni(const std::string &name, bool value);
    void setIntUni(const std::string &name, int value);
    void setFloatUni(const std::string &name, float value);
    void setVec3Uni(const std::string &name, float x, float y, float z);
    void setVec3Uni(const std::string &name, glm::vec3 param);
//    ~Shader();
};
#endif
