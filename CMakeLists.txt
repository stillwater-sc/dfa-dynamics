cmake_minimum_required(VERSION 3.0.0)
set(PROGRAM_NAME dfa-dynamics)
project(${PROGRAM_NAME} VERSION 0.1.0)

find_package(OpenGL REQUIRED)

add_executable(${PROGRAM_NAME} src/main.cpp src/glad.c)

target_include_directories(${PROGRAM_NAME} PRIVATE include)
target_link_directories(${PROGRAM_NAME} PRIVATE lib)
target_link_libraries(${PROGRAM_NAME} glfw3 OpenGL::GL)