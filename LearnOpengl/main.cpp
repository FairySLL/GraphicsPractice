#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "shader.h"
#include "image.h"

#include <cmath>
#include <iostream>

//GLM
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

float upDown(GLFWwindow *window, float opac);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //Make the context of our window the main context on the current thread
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initalize GLAD" << std::endl;
        return -1;
    }


    glEnable(GL_DEPTH_TEST);

    Shader ourShader("/home/fairysl/dev/Graphics/GraphicsPractice/LearnOpengl/shaders.vert",
                     "/home/fairysl/dev/Graphics/GraphicsPractice/LearnOpengl/shaders.frag");

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3 (0.0f, 0.0f, 0.0f),
        glm::vec3 (2.0f, 5.0f, -15.0f),
        glm::vec3 (-1.5f, -2.2f, -2.5f),
        glm::vec3 (-3.8f, -2.0f, -12.3f),
        glm::vec3 (2.4f, -0.4f, -3.5f),
        glm::vec3 (-1.7f, 3.0f, -7.5f),
        glm::vec3 (1.3f, -2.0f, -2.5f),
        glm::vec3 (1.5f, 2.0f, -1.5f),
        glm::vec3 (1.5f, 0.2f, -1.5f),
        glm::vec3 (-1.3f, 1.0f, -1.5f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    //Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Textures ---------------------------------------------------------------------------
    unsigned int texture1, texture2;

    //-----------------------------------
    // Texture1

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);


    //set wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("/home/fairysl/dev/Graphics/GraphicsPractice/LearnOpengl/container.jpg", &width,
                                    &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

//---------------------------
    // Texture2

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    //set wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("/home/fairysl/dev/Graphics/GraphicsPractice/LearnOpengl/awesomeface.png", &width, &height,
                     &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


   ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    float opac = 0.2f;


    //Rendering loop
    //------------------
    while (!glfwWindowShouldClose(window)) {

        //Variable for dynamic opacity change---


        //input---
        processInput(window);

        //rendering---
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Bind textures---
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //Turn shader on---
        ourShader.use();

        //create transformations---
        glm::mat4 model = glm::mat4(1.0f);
        //comment out previously used view
        //glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        /* Shows process of glm::LookAt constructed (somewhat) manually VVVV

        //camera position
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        //camera direction
        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
        //right axis
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        //up axis
        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
        //lookAt
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                            glm::vec3(0.0f,1.0f,0.0f));*/
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ),
                        glm::vec3(0.0, 0.0, 0.0),
                            glm::vec3(0.0, 1.0, 0.0));



        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 0.0f, 1.0f));
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");


        //Pass to shaders (3 ways)

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        //Note: We currently set the proj matrix to each frame, but since the proj matrix
        //rarely changes it's best practice to set it outside the main loop once
        // ourShader.setMat4("projection", projection); <- 3rd way, but not implemented in shader.h currently
       ourShader.setMat4("projection", projection);

        //render cube---
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;

            if (i % 3 == 0) {
                model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
            } else {
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f));
            }

            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        //change opacity with up/down arrows---
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            opac += 0.01f; // small increment per frame
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            opac -= 0.01f;
        ourShader.setFloat("opacity", opac);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

//helper functions ---
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float upDown(GLFWwindow *window, float opac) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        return opac + 0.1;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        return opac - 0.1;
}
