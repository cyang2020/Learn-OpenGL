#include <iostream>
#include <string.h>
#include <cmath>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Shader.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Mesh.hpp"


//VAO: Vertex Array Object(Header or description of data)
//VBO: Vertex Buffer Object(data)
GLuint VBO, VAO, EBO;
Camera camera(glm::vec3(0, 0, 3.0), 0.0f, -90.0f, glm::vec3(0, 1.0f, 0));
//Window dementions
const GLint WIDTH = 800, HEIGHT = 600;
float lastX = 400.0f;
float lastY = 300.0f;
bool firstTime = true;
//When creating some mesh or object:
//GenVAO, BindVAO, GenVBO, BindVBO, BUfferData(put data into VBO), AttrPtr(format the VAO), EnableIndex

void createTriangle() {
    GLfloat vertices[] = {
        //aPos                  aNormal            aTextureCoord
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));
            glEnableVertexAttribArray(2);
}

void processInput(GLFWwindow* window) {
    float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.Position += cameraSpeed * camera.Direction;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.Position -= cameraSpeed * camera.Direction;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.Position -= glm::normalize(glm::cross(camera.Direction, camera.WorldUp)) * cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.Position += glm::normalize(glm::cross(camera.Direction, camera.WorldUp)) * cameraSpeed;
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
       return;
    }
    if (firstTime) {
        lastX = xPos;
        lastY = yPos;
        firstTime = false;
    }
    float deltaX = xPos - lastX; 
    float deltaY = lastY - yPos;
    lastX = xPos;
    lastY = yPos;
    if (camera.Pitch > 89.0f) {
        camera.Pitch = 89.0f;
    }
    if (camera.Pitch < -89.0f) {
        camera.Pitch = -89.0f;
    }
    float sensitivity = 0.1f;
    deltaX *= sensitivity;
    deltaY *= sensitivity;
    camera.processMouseMovement(deltaX, deltaY);
}

unsigned int processTexture(const char* filePath, int num, GLint internalFormat, GLenum format, int textureSlot) {
    unsigned int textureBuffer;
    glGenTextures(num, &textureBuffer);
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    int textureWidth, textureHeight, nrChannel;
    unsigned char *data = stbi_load(filePath, &textureWidth, &textureHeight, &nrChannel, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Texture load failed");
    }
    stbi_image_free(data);
    return textureBuffer;
}

int s1 = -1;
void createIMGUI() {
    ImGui::Text("Options: ");
    ImGui::InputInt("Rotate Degree", &s1);
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
//   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   glfwSetCursorPosCallback(window, mouse_callback);
    
    //GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("initialisation failed");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    
    //    IMGUI Binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    bool changeDirLight = true;
    bool changePointLight = true;
    bool changeSpotLight = true;
    Shader* ourShader = new Shader("vertexShader.vert", "fragmentShader.frag");
    createTriangle();
    
    Material* ourMaterial = new Material(ourShader, processTexture("container2.png", 1, GL_RGBA, GL_RGBA, 0), processTexture("container2_specular.png", 1, GL_RGBA, GL_RGBA, 1), 32.0f);
    
    Light* ourLight = new Light(ourShader, glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    
    PointLight* ourPointLight = new PointLight(ourShader, glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    SpotLight* ourSpotLight = new SpotLight(ourShader, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), camera.Position, camera.Direction, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)));
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processInput(window);
        //IMGUI Windows
        {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("Change Light");
            ImGui::Checkbox("Directional Light", &changeDirLight);
            ImGui::Checkbox("Point Light", &changePointLight);
            ImGui::Checkbox("Spot Light", &changeSpotLight);
            ImGui::End();
        }
        ImGui::Render();
        if (changeDirLight) {
            ourLight = new Light(ourShader, glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
        } else {
            ourLight = new Light(ourShader, glm::vec3(-0.2f, 0.0f, -0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        }
        if (changePointLight) {
            ourPointLight = new PointLight(ourShader, glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
        } else {
            ourPointLight = new PointLight(ourShader, glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f);
        }
        if (changeSpotLight) {
            ourSpotLight = new SpotLight(ourShader, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), camera.Position, camera.Direction, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)));
        } else {
            ourSpotLight = new SpotLight(ourShader, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), camera.Position, camera.Direction, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)));
        }
        }
        //IMGUI Windows
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ourShader->use();
        glBindVertexArray(VAO);
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                for (int i = 0; i < 10; i ++) {
                    //Set MPV Matrices
                    glm::mat4 modelMat(1.0f); //TRS
                    modelMat = glm::translate(modelMat, cubePositions[i]);
                    float degree = 20.f * (i + 1);
                    modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(degree), glm::vec3(0.5f, 1.0f, 0.0f));
                    glm::mat4 projectionMat(1.0f);
                    projectionMat = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
                    glm::mat4 viewMat(1.0f);
                    viewMat = camera.getViewMatrix();
                    
                    //Set Uniform
                    glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
                    glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
                    glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));
                    
                    ourShader->setVec3Uni("viewPos", camera.Position);
                    ourLight->setUniforms();
                    ourPointLight->setUniforms();
                    ourSpotLight->setUniforms();
                    ourMaterial->setUniforms();
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);
    
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

int main1() {
    GLfloat vertices[] = {
        //aPos                  aNormal            aTextureCoord
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
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
//   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   glfwSetCursorPosCallback(window, mouse_callback);
    
    //GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("initialisation failed");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    
    //    IMGUI Binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    bool changeDirLight = true;
    bool changePointLight = true;
    bool changeSpotLight = true;
    
    Shader* ourShader = new Shader("vertexShader.vert", "fragmentShader.frag");
    Material* ourMaterial = new Material(ourShader, processTexture("container2.png", 1, GL_RGBA, GL_RGBA, 0), processTexture("container2_specular.png", 1, GL_RGBA, GL_RGBA, 1), 32.0f);
    Light* ourLight = new Light(ourShader, glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    PointLight* ourPointLight = new PointLight(ourShader, glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    SpotLight* ourSpotLight = new SpotLight(ourShader, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), camera.Position, camera.Direction, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)));
    
    Mesh cube(vertices);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processInput(window);
        //IMGUI Windows
        {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("Change Light");
            ImGui::Checkbox("Directional Light", &changeDirLight);
            ImGui::Checkbox("Point Light", &changePointLight);
            ImGui::Checkbox("Spot Light", &changeSpotLight);
            ImGui::End();
        }
        ImGui::Render();
        if (changeDirLight) {
            ourLight = new Light(ourShader, glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
        } else {
            ourLight = new Light(ourShader, glm::vec3(-0.2f, 0.0f, -0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        }
        if (changePointLight) {
            ourPointLight = new PointLight(ourShader, glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
        } else {
            ourPointLight = new PointLight(ourShader, glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.09f, 0.032f);
        }
        if (changeSpotLight) {
            ourSpotLight = new SpotLight(ourShader, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), camera.Position, camera.Direction, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)));
        } else {
            ourSpotLight = new SpotLight(ourShader, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), camera.Position, camera.Direction, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)));
        }
        }
        //IMGUI Windows
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ourShader->use();
        for (int i = 0; i < 10; i ++) {
            //Set MPV Matrices
            glm::mat4 modelMat(1.0f); //TRS
            modelMat = glm::translate(modelMat, cubePositions[i]);
            float degree = 20.f * (i + 1);
            modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(degree), glm::vec3(0.5f, 1.0f, 0.0f));
            glm::mat4 projectionMat(1.0f);
            projectionMat = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
            glm::mat4 viewMat(1.0f);
            viewMat = camera.getViewMatrix();
            
            //Set Uniform
            glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(ourShader -> ID, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));
            
            ourShader->setVec3Uni("viewPos", camera.Position);
            ourLight->setUniforms();
            ourPointLight->setUniforms();
            ourSpotLight->setUniforms();
            ourMaterial->setUniforms();
            cube.Draw(ourShader);
        }
        glUseProgram(0);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
