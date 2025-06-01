cmake_minimum_required(VERSION 3.0)

project(CarlPhysicsEngine VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(glad STATIC include/glad/glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
target_include_directories(glad PUBLIC include/glad)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/simulation.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_OSX_ARCHITECTURES "arm64")

add_executable(CarlPhysicsEngine ${SOURCES})

target_link_libraries(CarlPhysicsEngine PRIVATE glad glfw OpenGL::GL)
