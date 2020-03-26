
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include "Shader.hpp"
#include <string>
#include <sstream>
//FileStream -> StringStream -> String -> char*
Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::string vertexCode;
    std::string fragmentCode;
    
    std::ifstream vertexFile;
    std::ifstream fragmentFile;
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        std::stringstream vertexStringStream;
        std::stringstream fragmentStringStream;
        vertexStringStream << vertexFile.rdbuf();
        fragmentStringStream << fragmentFile.rdbuf();
        
        vertexFile.close();
        fragmentFile.close();
        
        vertexCode = vertexStringStream.str();
        fragmentCode = fragmentStringStream.str();
    } catch (std::ifstream::failure e) {
        printf("ERROR: Unable to read shader files.");
    }
    
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();
    
    //load the shaders
    unsigned int vertexShader;
    int success;
    char infoLog[512];
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Unable to compile Vertex Shader");
    }
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Unable to compile Fragment Shader");
    }
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        printf("SHADER::PROGRAM::LINKING_FAILED");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBoolUni(const std::string &name, bool value){
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setIntUni(const std::string &name, int value){
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloatUni(const std::string &name, float value){
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setVec3Uni(const std::string &name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
void Shader::setVec3Uni(const std::string &name, glm::vec3 param) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), param.x, param.y, param.z);
}
