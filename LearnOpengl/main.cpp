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

//Github test

/*
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos, 1.0);\n"
    "ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(ourColor, 1.0);\n"
    "}\0";
    */

/*
const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";*/




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

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initalize GLAD" << std::endl;
        return -1;
    }
    //Location of lower left corner of window and size
    //glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    Shader ourShader("/home/fairysl/dev/Graphics/GraphicsPractice/LearnOpengl/shaders.vert", "/home/fairysl/dev/Graphics/GraphicsPractice/LearnOpengl/shaders.frag");
    //Build and compile our shader program
    // -----------------------------------

    float vertices[] = {
        //positions        //colors         //texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
        //1st triangle
        /* -0.5f, 0.5f, 0.0f,
         -0.5f, -0.5f, 0.0f,
         -1.0f, 0.0f, 0.0f,*/
        //2nd triangle
        /* 0.5f, 0.5f, 0.0f,
          1.0f, 0.0f, 0.0f,
          0.5f, -0.5f, 0.0f*/


    };
    /*
        float vertices2[] = {
            0.5f, 0.5f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f
        };*/

    /*float vertices[] = {
        0.5f, 0.5f, 0.0f, //top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, //bottom left
        -0.5f, 0.5f, 0.0f //top left
    };
*/
    unsigned int indices[] = {
        0, 1, 3, //First Triangle
        1, 2, 3 //second triangle
    };




    //Vertex Buffer Object
    //------------------------
    unsigned int VBO;//, VBO2;

    glGenBuffers(1, &VBO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    /*/ 2nd triangle

    glGenBuffers(1, &VBO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
*/
    //------------------
/*
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //error check
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
*/
    //Fragment shader-------------------------------------/*
/*
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //error check
    int success2;
    char infoLog2[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);
    if (!success2) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
    }
    /*
        unsigned int fragmentShader2;
        fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
        glCompileShader(fragmentShader2);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);
        if (!success2) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
            std::cout << "ERROR::SHADER::FRAGMENT2::COMPILATION_FAILED\n" << infoLog2 << std::endl;
        }*/
/*
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //error check
    int success3;
    char infoLog3[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success3);
    if (!success3) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog3);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog3 << std::endl;
    }*/
    /*
        unsigned int shaderProgram2;
        shaderProgram2 = glCreateProgram();

        glAttachShader(shaderProgram2, vertexShader);
        glAttachShader(shaderProgram2, fragmentShader2);
        glLinkProgram(shaderProgram2);

        glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success3);
        if (!success3) {
            glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog3);
            std::cout << "ERROR::SHADER::PROGRAM2::LINKING_FAILED\n" << infoLog3 << std::endl;
        }*/
/*
    //glUseProgram(shaderProgram2);
    glUseProgram(shaderProgram);


    //After successful link we don't need the shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //glDeleteShader(fragmentShader2);*/

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);


    // Vertex Array Object
    //-----------------------------
    unsigned int VAO, VAO2;
    glGenVertexArrays(1, &VAO);

    //Bind vertex array object
    glBindVertexArray(VAO);

    //Copy vertices array in a buffer for openGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Set our vertex attributes pointers //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    //Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //Texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    /*/VAO object 2 ------------------------

    glGenVertexArrays(1, &VAO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

*/


    //Element Buffer Object
    //--------------------------

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    // Textures ---------------------------------------------------------------------------



    unsigned int texture, texture2;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);


    //set wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("/home/fairysl/dev/Graphics/GraphicsPractice/LearnOpengl/container.jpg", &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);


    //set wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   data = stbi_load("/home/fairysl/dev/Graphics/GraphicsPractice/LearnOpengl/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    ourShader.setInt("texture2", 1);
    ourShader.setFloat("opacity", 0.1);
    float opac = 0.1;

    //glm ----------------------------------------------------------------

/*
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;*/

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));







    //Rendering loop
    //------------------
    while (!glfwWindowShouldClose(window)) {
        //input
        processInput(window);
        //float swag = upDown(window, opac);

        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);




        /*float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
       // float offset = 0.5f;
        //ourShader.setFloat("moveRight", offset);
        glm::mat4 trans = glm::mat4(1.0f);

        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");


        trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));


        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        //Texture ----------------------
        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);


        ourShader.use();
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            opac += 0.01f;  // small increment per frame
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            opac -= 0.01f;
        ourShader.setFloat("opacity", opac);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmt = static_cast<float>(sin(glfwGetTime()));
        trans = glm::scale(trans, glm::vec3(std::abs(scaleAmt), std::abs(scaleAmt), std::abs(scaleAmt)));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        //--------------------------------
     //   glBindVertexArray(VAO);
//glDrawArrays(GL_TRIANGLES, 0, 3);
        /*
                glUseProgram(shaderProgram2);
                glBindVertexArray(VAO2);
                glDrawArrays(GL_TRIANGLES, 0, 3);*/

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        //check and call events and swap the buffers

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

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
