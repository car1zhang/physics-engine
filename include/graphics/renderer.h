#pragma once

#include "bodies/body.h"
#include "graphics/shader.h"

#include <glad/glad.h>
#include <vector>


class Renderer {
public:
    Renderer() = default;
    Renderer(const std::string& mesh_path);
    ~Renderer();

    void DrawBodies(Shader* shader);

    std::string get_mesh_path() const { return mesh_path_; }
    void emplace_body(Body* body) { bodies_.emplace_back(body); }
    void remove_body(Body* body) { bodies_.erase(std::find(bodies_.begin(), bodies_.end(), body)); }

private:
    const std::string mesh_path_;

    std::vector<Body*> bodies_;

    float* CalculateNormals_(float* vertices, uint* indices);

    GLuint vao_, vbo_, nvbo_, ebo_;

    float* vertices_;
    uint* indices_;
};
