#pragma once

#include "bodies/body.h"
#include "graphics/shader.h"


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
    void ReadMesh_(const std::string& mesh_path);
    void CalculateNormals_();
    void CreateBuffers_();

    std::vector<Body*> bodies_;

    const std::string mesh_path_;
    unsigned int vertex_count_;
    float* vertices_;
    float* normals_;
    unsigned int triangle_count_;
    uint* indices_;
    GLuint vao_, vbo_, nvbo_, ebo_;
};
