#define GLFW_INCLUDE_NONE

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/renderers/cube_renderer.h"
#include "graphics/graphics_manager.h"
#include "graphics/shader.h"
#include "constants.h"


GraphicsManager::GraphicsManager() {
    CreateWindow_();
    shader_ = new Shader(constants::kVertexShaderPath, constants::kFragmentShaderPath);
    shader_->Use();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    cube_renderer_ = new CubeRenderer();
}


GraphicsManager::~GraphicsManager() {
    delete shader_;

    glfwDestroyWindow(window_);
    glfwTerminate();
}


void GraphicsManager::Draw() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_->SetMat4("view", camera_->get_view_matrix());
    shader_->SetMat4("projection", camera_->get_projection_matrix());

    cube_renderer_->DrawCubes(shader_);

    glfwSwapBuffers(window_);
}


void GraphicsManager::CreateWindow_() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window_ = glfwCreateWindow(constants::kWindowWidth, constants::kWindowHeight, constants::kProgramName, nullptr, nullptr);
    if (!window_) {
        std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window_);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    glViewport(0, 0, width, height);
}
