//
//  Model.hpp
//  OpenGL
//
//  Created by Casper Yang on 5/9/20.
//  Copyright © 2020 Casper Yang. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <assimp/Importer.hpp>
#include "Shader.hpp"
#include "Mesh.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

class Model {
public:
    Model(std::string path);
    void Draw(Shader* shader);
    GLint TextureFormFile(const char* path, std::string &directory, bool gamma = false);
    
private:
    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTex;
    std::string directory;
    void loadModel(std::string path);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif /* Model_hpp */
