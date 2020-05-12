//
//  Mesh.cpp
//  OpenGL
//
//  Created by Casper Yang on 5/8/20.
//  Copyright © 2020 Casper Yang. All rights reserved.
//

#include "Mesh.hpp"
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures){
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->setupMesh();
}

Mesh::Mesh(float vertices[]) {
    this->vertices.resize(36);
    std::memcpy(&(this->vertices[0]), vertices, 36 * 8 * sizeof(float));
    setupMesh();
}

void Mesh::Draw(Shader* shader){
    unsigned int diffuseNbr = 1;
    unsigned int specularNbr = 1;
    for (GLuint i = 0; i < this->textures.size(); i ++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::stringstream ss;
        std::string number;

        if (this->textures[i].type == "texture_diffuse") {
            ss << diffuseNbr++;
        }
        else if (textures[i].type == "texture_specular") {
            ss << specularNbr++;
        }
        number = ss.str();
        shader -> setIntUni(("material." + this->textures[i].type).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
    shader -> setFloatUni("material.shininess", 16.0f);
    
    glBindVertexArray(this -> VAO);
    if (this->indices.size() == 0) {
        glDrawArrays(GL_TRIANGLES, 0, 36);
    } else {
        glDrawElements(GL_TRIANGLES, (GLsizei)this -> indices.size(), GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
    for (GLuint i = 0; i < this->textures.size(); i ++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Mesh::setupMesh(){
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->indices.size(), &this->indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
    
    glBindVertexArray(0);
}
