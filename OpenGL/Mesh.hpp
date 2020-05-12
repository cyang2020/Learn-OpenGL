#ifndef Mesh_hpp
#define Mesh_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Material.hpp"
#include "Shader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};
struct Texture {
    unsigned int id;
    std::string type;
    aiString path;
};

class Mesh{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    Mesh(float vertices[]);
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
    void Draw(Shader* shader);
    
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};
#endif /* Mesh_hpp */
