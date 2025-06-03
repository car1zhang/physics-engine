#pragma once
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

    GLuint shader_program_;
    GLuint shader_program_1;
    GLuint vaos_[2], vbos_[2], ebo_;
};
