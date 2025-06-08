#pragma once

#include "graphics/shader.h"
#include "graphics/camera.h"
#include "graphics/renderers/cube_renderer.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


class GraphicsManager {
public:
    GraphicsManager();
    ~GraphicsManager();

    void Draw();

    GLFWwindow* get_window() { return window_; }

    CubeRenderer* get_cube_renderer() { return cube_renderer_; }

    void set_camera(Camera* const camera) { camera_ = camera; }

private:
    void CreateWindow_();
    void InitializeShaders_();
    GLuint LoadShader_(const std::string& filepath, GLenum shader_type);

    GLFWwindow* window_;

    Shader* shader_;

    Camera* camera_;

    CubeRenderer* cube_renderer_; // TODO: have a vector of generic object renderers
};
