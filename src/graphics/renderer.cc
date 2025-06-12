#include <fstream>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "graphics/renderer.h"


Renderer::Renderer(const std::string& mesh_path) : mesh_path_(mesh_path) { // TODO: get mesh from mesh path
    std::ifstream mesh_file;
    mesh_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        mesh_file.open(mesh_path);
        if (!mesh_file.is_open()) {
            std::cerr << "ERROR: Failed to open mesh file: " << mesh_path << std::endl;
        }

        int vertex_count;
        mesh_file >> vertex_count;
        vertices_ = new float[vertex_count * 3];
        for (int i = 0; i < vertex_count; i++) {
            mesh_file >> vertices_[i * 3];
            mesh_file >> vertices_[i * 3 + 1];
            mesh_file >> vertices_[i * 3 + 2];
        }

        int triangle_count;
        mesh_file >> triangle_count;
        indices_ = new uint[triangle_count * 3];
        for (int i = 0; i < triangle_count; i++) {
            mesh_file >> indices_[i * 3];
            mesh_file >> indices_[i * 3 + 1];
            mesh_file >> indices_[i * 3 + 2];
        }
        glGenVertexArrays(1, &vao_);
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &ebo_);

        glBindVertexArray(vao_);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, vertex_count * 3 * sizeof(float), vertices_, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle_count * 3 * sizeof(uint), indices_, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR: Failed to read mesh file: " << mesh_path << std::endl;
    }
}



Renderer::~Renderer() { // be sure to delete the boxes elsewhere
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
    delete[] vertices_;
    delete[] indices_;
}


void Renderer::DrawBodies(Shader* shader) {
    glBindVertexArray(vao_);

    for (Body* body : bodies_) {
        glm::mat4 model_matrix = glm::mat4(1.0f);

        // TODO: translate vector data types to glm::vec3

        model_matrix = glm::translate(model_matrix, body->get_pos());

        model_matrix = glm::rotate(model_matrix, glm::radians(body->get_rot_deg()), body->get_rot_axis());

        model_matrix = glm::scale(model_matrix, body->get_scale());

        shader->SetMat4("model", model_matrix);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}


float* Renderer::CalculateNormals_(float* vertices_, uint* indices_) {
    static float normals[24];

    for (int i = 0; i < 24; i++) {
        normals[i] = 0.0f;
    }

    for (int i = 0; i < 36; i += 3) {
        uint v0 = indices_[i];
        uint v1 = indices_[i + 1];
        uint v2 = indices_[i + 2];

        glm::vec3 p0(vertices_[v0 * 3], vertices_[v0 * 3 + 1], vertices_[v0 * 3 + 2]);
        glm::vec3 p1(vertices_[v1 * 3], vertices_[v1 * 3 + 1], vertices_[v1 * 3 + 2]);
        glm::vec3 p2(vertices_[v2 * 3], vertices_[v2 * 3 + 1], vertices_[v2 * 3 + 2]);

        glm::vec3 edge1 = p1 - p0;
        glm::vec3 edge2 = p2 - p0;
        glm::vec3 face_normal = glm::normalize(glm::cross(edge1, edge2));

        normals[v0 * 3] += face_normal.x;
        normals[v0 * 3 + 1] += face_normal.y;
        normals[v0 * 3 + 2] += face_normal.z;

        normals[v1 * 3] += face_normal.x;
        normals[v1 * 3 + 1] += face_normal.y;
        normals[v1 * 3 + 2] += face_normal.z;

        normals[v2 * 3] += face_normal.x;
        normals[v2 * 3 + 1] += face_normal.y;
        normals[v2 * 3 + 2] += face_normal.z;
    }

    for (int i = 0; i < 8; i++) {
        glm::vec3 normal(normals[i * 3], normals[i * 3 + 1], normals[i * 3 + 2]);
        normal = glm::normalize(normal);
        normals[i * 3] = normal.x;
        normals[i * 3 + 1] = normal.y;
        normals[i * 3 + 2] = normal.z;
    }

    return normals; // TODO: don't return, just make a vbo and bind to vao
}
