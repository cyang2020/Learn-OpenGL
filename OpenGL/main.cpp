#include <iostream>
#include <string.h>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include "Shader.hpp"

//VAO: Vertex Array Object(Header or description of data)
//VBO: Vertex Buffer Object(data)
GLuint VBO, VAO;

//Window dementions
const GLint WIDTH = 800, HEIGHT = 600;
float triOffset = 0.0f;
float triMaxMove = 0.7f;
float triMove = 0.005f;

//When creating some mesh or object:
//GenVAO, BindVAO, GenVBO, BindVBO, BUfferData(put data into VBO), AttrPtr(format the VAO), EnableIndex
void createTriangle(){
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    glGenVertexArrays(1, &VAO); //generating 1 array stored in VAO
    glBindVertexArray(VAO); //binding the cur array with VAO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
            glEnableVertexAttribArray(0); //enable index 0
    
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
            glEnableVertexAttribArray(1); //enable index 1

//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0); //unbind VAO
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
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
    
    Shader* ourShader = new Shader("vertexShader.txt", "fragmentShader.txt");
    createTriangle();
   
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ourShader->use();
            glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        glUseProgram(0);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
