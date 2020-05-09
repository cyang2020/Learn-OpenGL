//
//  Mesh.hpp
//  OpenGL
//
//  Created by Casper Yang on 5/8/20.
//  Copyright © 2020 Casper Yang. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Material.hpp"
#include "Shader.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 TexCoord;
};
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Mesh(float vertices[]);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader* shader);
    
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};
#endif /* Mesh_hpp */
