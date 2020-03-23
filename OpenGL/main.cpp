#include <iostream>
#include <string.h>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.hpp"

//VAO: Vertex Array Object(Header or description of data)
//VBO: Vertex Buffer Object(data)
GLuint VBO, VAO, EBO;
Camera camera(glm::vec3(0, 0, 3.0), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
//Window dementions
const GLint WIDTH = 800, HEIGHT = 600;
float triOffset = 0.0f;
float triMaxMove = 0.7f;
float triMove = 0.005f;

//When creating some mesh or object:
//GenVAO, BindVAO, GenVBO, BindVBO, BUfferData(put data into VBO), AttrPtr(format the VAO), EnableIndex
void createTriangle(){
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 2, //EBO 2 triangles make up one Rectangle
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO); //generating 1 array stored in VAO
    glBindVertexArray(VAO); //binding the cur array with VAO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
            glEnableVertexAttribArray(0); //enable index 0 = loc
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
//            glEnableVertexAttribArray(1); //enable index 1 = color
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
            glEnableVertexAttribArray(2); //enable index 2 = texture
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void processTexture(unsigned int* textureBuffer, int num, bool RGB, char* filePath, bool flip) {
    glGenTextures(num, &(*textureBuffer));
    glBindTexture(GL_TEXTURE_2D, *textureBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (flip){
        stbi_set_flip_vertically_on_load(true);
    }
    int textureWidth, textureHeight, nrChannel;
    unsigned char *data = stbi_load(filePath, &textureWidth, &textureHeight, &nrChannel, 0);
    if (data) {
        if (RGB) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Texture load failed");
    }
    stbi_image_free(data);
}

int main() {
    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    // Initalize GLFW (GLFW for managing windows)
    if (!glfwInit()) {
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //Create a window
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OPENGL", NULL, NULL);
    if (!window) {
        printf("Window not created");
        glfwTerminate();
        return 1;
    }
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("initialisation failed");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);

    Shader* ourShader = new Shader("vertexShader.txt", "fragmentShader.txt");
    createTriangle();
    
    //Attach Texture:
    unsigned int textureBufferA;
    unsigned int* texturePtr = &textureBufferA;
    char filePathA[] = "container.jpg";
    processTexture(texturePtr, 1, true, filePathA, false);

    unsigned int textureBufferB;
    texturePtr = &textureBufferB;
    char filePathB[] = "awesomeface.png";
    processTexture(texturePtr, 1, false, filePathB, true);

    ourShader -> use();
    ourShader -> setIntUni("ourTex", 0);
    ourShader -> setIntUni("ourFaceTex", 1);
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glm::mat4 trans(1.0f);
        //Translate > Rotate > scale
//        trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0f));
//        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
        ourShader->use();
        glBindVertexArray(VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                for (int i = 0; i < 10; i ++) {
                    glm::mat4 modelMat(1.0f);
                    modelMat = glm::translate(modelMat, cubePositions[i]);
                    modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(20.f * (i + 1)), glm::vec3(0.5f, 1.0f, 0.0f));
                    glm::mat4 viewMat(1.0f);
                    viewMat = camera.getViewMatrix();
                    glm::mat4 projectionMat(1.0f);
                    projectionMat = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
            //      glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
                    glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
                    glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
                    glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, textureBufferA);
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, textureBufferB);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //                trans = glm::mat4(1.0f);
    //                //Translate > Rotate > scale
    //                trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
    //                trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    //                trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    //                glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
    //
    //                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
                }
        glBindVertexArray(0);
        glUseProgram(0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
