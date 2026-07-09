cmake_minimum_required(VERSION 4.2)
project(OpenGLAimTrainer)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(LearnOpengl main.cpp src/glad.c
        shader.cpp
        shader.h
        image.h
        camera.h)

target_include_directories(LearnOpengl PRIVATE include)

target_link_libraries(LearnOpengl
    OpenGL::GL
    glfw
        dl
    )

