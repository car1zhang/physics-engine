#pragma once
#include "graphics/shader.h"
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
};
