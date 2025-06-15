cmake_minimum_required(VERSION 3.5)

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
    src/main.cc
    src/simulation.cc
    src/controller.cc
    src/camera.cc

    src/bodies/body_manager.cc
    src/bodies/body.cc

    src/physics/components/gravity_component.cc

    src/graphics/graphics_manager.cc
    src/graphics/shader.cc
    src/graphics/renderer.cc
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_OSX_ARCHITECTURES "arm64")

add_executable(CarlPhysicsEngine ${SOURCES})

target_link_libraries(CarlPhysicsEngine PRIVATE glad glfw OpenGL::GL)
