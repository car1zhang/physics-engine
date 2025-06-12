#pragma once

#include <map>

#include "graphics/renderer.h"
#include "camera.h"


class GraphicsManager {
public:
    GraphicsManager();
    ~GraphicsManager();

    void Draw(Camera* camera, GLFWwindow* window);

    Renderer* get_renderer(BodyType type) { return renderers_[type]; }

private:
    void InitializeShaders_();
    GLuint LoadShader_(const std::string& filepath, GLenum shader_type);

    Shader shader_;

    std::map<BodyType, Renderer*> renderers_;
};
