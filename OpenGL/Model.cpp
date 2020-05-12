//
//  Model.cpp
//  OpenGL
//
//  Created by Casper Yang on 5/9/20.
//  Copyright © 2020 Casper Yang. All rights reserved.
//

#include "Model.hpp"
Model::Model(std::string path){
    loadModel(path);
}
void Model::Draw(Shader* shader) {
    for (GLuint i = 0; i < meshes.size(); i ++) {
        meshes[i].Draw(shader);
    }
}
void Model::loadModel(std::string path){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !(scene -> mRootNode)) {
        std::cout << "ASSIMP ERROR" << importer.GetErrorString() << std::endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));
    this->processNode(scene -> mRootNode, scene);
}
void Model::processNode(aiNode* node, const aiScene* scene) {
    for (GLuint i = 0; i < node->mNumMeshes; i ++) {
        aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(processMesh(curMesh, scene));
    }
    for (GLuint i = 0; i < node->mNumChildren; i ++) {
        processNode(node->mChildren[i], scene);
    }
}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> tempVertices;
    std::vector<GLuint> tempIndices;
    std::vector<Texture> tempTextures;
    for (GLuint i = 0; i < mesh->mNumVertices; i ++) {
        Vertex tempVertex;
        glm::vec3 temVec;
        temVec.x = mesh->mVertices[i].x;
        temVec.y = mesh->mVertices[i].y;
        temVec.z = mesh->mVertices[i].z;
        tempVertex.Position = temVec;
        
        temVec.x = mesh->mNormals[i].x;
        temVec.y = mesh->mNormals[i].y;
        temVec.z = mesh->mNormals[i].z;
        tempVertex.Normal = temVec;
        
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            tempVertex.TexCoord = vec;
        } else {
            tempVertex.TexCoord = glm::vec2(0.0f, 0.0f);
        }
        tempVertices.push_back(tempVertex);
    }
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            tempIndices.push_back(face.mIndices[j]);
    }
    
    if (mesh->mMaterialIndex >= 0){
        aiMaterial* mat = scene -> mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = this -> loadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
        tempTextures.insert(tempTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = this -> loadMaterialTextures(mat, aiTextureType_SPECULAR , "texture_specular");
        tempTextures.insert(tempTextures.end(), specularMaps.begin(), specularMaps.end());
    }
    return Mesh(tempVertices, tempIndices, tempTextures);
}
std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName){
    std::vector<Texture> textures;
    for (GLuint i = 0; i < mat->GetTextureCount(type); i ++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        GLboolean skip = false;
        for (GLuint j = 0; j < loadedTex.size(); j ++) {
            if (loadedTex[j].path == str) {
                textures.push_back(loadedTex[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture;
            texture.id = TextureFormFile(str.C_Str(), directory);
            texture.path = str;
            texture.type = typeName;
            textures.push_back(texture);
            loadedTex.push_back(texture);
        }
    }
    return textures;
}
GLint Model::TextureFormFile(const char* path, std::string &directory, bool gamma) {
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

