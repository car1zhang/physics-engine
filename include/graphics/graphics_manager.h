#pragma once
#include "graphics/shader.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string>

class GraphicsManager {
public:
    GraphicsManager();
    ~GraphicsManager();

    void Draw();

    GLFWwindow* get_window() { return window_; }

private:
    void CreateWindow_();
    void InitializeShaders_();
    GLuint LoadShader_(const std::string& filepath, GLenum shader_type);

    GLFWwindow* window_;

    Shader* shader_;

    GLuint vbo_, vao_;

    glm::vec3 cube_positions[10] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
};
