#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "shader.h"
#include "image.h"
#include "camera.h"

#include <cmath>
#include <iostream>
#include <string>
#include <algorithm> //for min max

//GLM
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

float upDown(GLFWwindow* window, float opac);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //Make the context of our window the main context on the current thread
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initalize GLAD" << std::endl;
        return -1;
    }


    glEnable(GL_DEPTH_TEST);

    //Reference RESOURCES_DIR in CMakeList.txt
    std::string vertPath = std::string(RESOURCES_DIR) + "shaders/shaders.vert";
    std::string fragPath = std::string(RESOURCES_DIR) + "shaders/shaders.frag";

    Shader mainShader(vertPath.c_str(),
                      fragPath.c_str());

    //Crosshair shaders

    std::string crossVPath = std::string(RESOURCES_DIR) + "shaders/crosshair.vert";
    std::string crossFPath = std::string(RESOURCES_DIR) + "shaders/crosshair.frag";

    Shader crossShader(crossVPath.c_str(),
                       crossFPath.c_str());

    float crosshairV[] = {
        0.0, 0.04, 0.0, //Top
        -0.04, -0.04, 0.0, //bottom left
        0.04, -0.04, 0.0 //bottom right
    };


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
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -1.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    //Crosshair attribs/binding ------------------------------------------------------------
    unsigned int crossVBO, crossVAO;
    glGenVertexArrays(1, &crossVAO);
    glGenBuffers(1, &crossVBO);

    glBindVertexArray(crossVAO);

    glBindBuffer(GL_ARRAY_BUFFER, crossVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairV), crosshairV, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //End of crosshair --------------------------------------------------------------------------
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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
    std::string contPath = std::string(RESOURCES_DIR) + "container.jpg";
    unsigned char* data = stbi_load(contPath.c_str(), &width,
                                    &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
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
    std::string facePath = std::string(RESOURCES_DIR) + "awesomeface.png";
    data = stbi_load(facePath.c_str(), &width, &height,
                     &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    mainShader.use();
    mainShader.setInt("texture1", 0);
    mainShader.setInt("texture2", 1);
    float opac = 0.2f;


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    bool shouldRender[10];
    for (int j = 0; j < 10; j++)
        shouldRender[j] = true;

    //Rendering loop
    //------------------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        bool hit = false;


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
        mainShader.use();

        //pass projection matrix to shader
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f,
                                                100.0f);
        mainShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        mainShader.setMat4("view", view);

        //render cube---
        glBindVertexArray(VAO);
        int hitIndex = -1;
        for (unsigned int i = 0; i < 10; i++)
        {
            if (!shouldRender[i])
                continue;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;


            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));


            mainShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);

            //check for crosshair overlap:

            //Get inverse of model to use matrix multiplication to put our camera
            //position and direction into local space
            glm::mat4 localModel = glm::inverse(model);

            //multiply by local(obj) space coords to translate WORLD position
            //and WORLD direction into LOCAL space
            //We need to do this by mat4 because that'ss how we build our model matrix initially,
            //even though for actual check we will only need vec3's
            glm::vec4 rayOriginLocal4 = localModel * glm::vec4(camera.Position, 1.0f);
            glm::vec4 rayDirLocal4 = localModel * glm::vec4(camera.Front, 0.0f);

            //Our vec3's!!!
            glm::vec3 rayOriginLocal = glm::vec3(rayOriginLocal4);
            glm::vec3 rayDirLocal = glm::vec3(rayDirLocal4);

            // t = (boundary - origin) / direction
            // we know boundary is [-0.5,0.5] for all xyz

            double tMinX = (-0.5 - rayOriginLocal.x) / rayDirLocal.x;
            double tMaxX = (0.5 - rayOriginLocal.x) / rayDirLocal.x;

            //min could be larger than max depending on position in local space
            //This ensures min is the enter and max is the exit point
            if (tMinX > tMaxX)
                std::swap(tMinX, tMaxX);

            double tMinY = (-0.5 - rayOriginLocal.y) / rayDirLocal.y;
            double tMaxY = (0.5 - rayOriginLocal.y) / rayDirLocal.y;

            if (tMinY > tMaxY)
                std::swap(tMinY, tMaxY);

            double tMinZ = (-0.5 - rayOriginLocal.z) / rayDirLocal.z;
            double tMaxZ = (0.5 - rayOriginLocal.z) / rayDirLocal.z;

            if (tMinZ > tMaxZ)
                std::swap(tMinZ, tMaxZ);

            //Find the overlap
            double tEnter = std::max(tMinX, std::max(tMinY, tMinZ));
            double tExit = std::min(tMaxX, std::min(tMaxY, tMaxZ));

            if (tEnter <= tExit && tExit >= 0)
            {
                hit = true;
                hitIndex = i;
            }
            if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && hitIndex != -1)
                shouldRender[hitIndex] = false;
        }


        //change opacity with up/down arrows---
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            opac += 0.01f; // small increment per frame
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            opac -= 0.01f;
        mainShader.setFloat("opacity", opac);

        glDisable(GL_DEPTH_TEST);

        crossShader.use();
        crossShader.setBool("hit", hit);
        glBindVertexArray(crossVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glEnable(GL_DEPTH_TEST);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);


    glfwTerminate();
    return 0;
}

//helper functions ---
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

float upDown(GLFWwindow* window, float opac)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        return opac + 0.1;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        return opac - 0.1;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
