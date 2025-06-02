#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "graphics_manager.h"
#include "constants.h"

GraphicsManager::GraphicsManager() {
    // window
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

    // shaders
    int success;
    char info_log[512];

    const char* vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to compile vertex shader\n" << info_log << std::endl;
    }

    const char* fragment_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to compile fragment shader\n" << info_log << std::endl;
    }

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
