#define GLFW_INCLUDE_NONE
#include <iostream>
#include <fstream>
#include <sstream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "graphics_manager.h"
#include "constants.h"

GraphicsManager::GraphicsManager() {
    CreateWindow_();
    InitializeShaders_();

    // things to draw
    float ndc_vertices[] = {
        -0.5f, 0.5f, 0.0f,
        -0.8f, -0.5f, 0.0f,
        -0.2f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.2f, -0.5f, 0.0f,
        0.8f, -0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        3, 4, 5
    };
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ndc_vertices), ndc_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

GraphicsManager::~GraphicsManager() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void GraphicsManager::Draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program_);
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window_);
}

void GraphicsManager::CreateWindow_() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window_ = glfwCreateWindow(constants::kWindowWidth, constants::kWindowHeight, constants::kProgramName, nullptr, nullptr);
    if (!window_) {
        std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    glViewport(0, 0, width, height);
}

unsigned int GraphicsManager::LoadShader_(const std::string& filepath, GLenum shader_type) {
    std::ifstream shader_file;
    std::stringstream shader_stream;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shader_file.open(filepath);
        shader_stream << shader_file.rdbuf();
        shader_file.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR: Failed to read shader file: " << filepath << std::endl;
    }
    std::string shader_string = shader_stream.str();
    const char* shader_source = shader_string.c_str(); // necessary bc of some memory copy quirk

    int success;
    char info_log[512];
    unsigned int shader;
    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to compile shader\n" << info_log << std::endl;
        return 0;
    }

    return shader;
}

void GraphicsManager::InitializeShaders_() {
    unsigned int vertex_shader = LoadShader_("../shaders/vertex.vert", GL_VERTEX_SHADER); // relocate later
    unsigned int fragment_shader = LoadShader_("../shaders/fragment.frag", GL_FRAGMENT_SHADER);

    int success;
    char info_log[512];
    shader_program_ = glCreateProgram();
    glAttachShader(shader_program_, vertex_shader);
    glAttachShader(shader_program_, fragment_shader);
    glLinkProgram(shader_program_);
    glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program_, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to link shader program\n" << info_log << std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}
