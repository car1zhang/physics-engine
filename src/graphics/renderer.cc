#include <fstream>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "graphics/renderer.h"


Renderer::Renderer(const std::string& mesh_path) : mesh_path_(mesh_path) {
    ReadMesh_(mesh_path);
    // CalculateNormals_();
    CreateBuffers_();
}


Renderer::~Renderer() { // be sure to delete the boxes elsewhere
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    // glDeleteBuffers(1, &ebo_);
    delete[] vertices_;
    // delete[] indices_;
}


void Renderer::DrawBodies(Shader* shader) {
    glBindVertexArray(vao_);

    for (Body* body : bodies_) {
        glm::mat4 model_matrix = glm::mat4(1.0f);

        model_matrix = glm::translate(model_matrix, body->get_pos().to_glm());

        model_matrix = glm::rotate(model_matrix, glm::radians(body->get_rot_deg()), body->get_rot_axis().to_glm());

        model_matrix = glm::scale(model_matrix, body->get_scale().to_glm());

        shader->SetMat4("model", model_matrix);

        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, triangle_count_ * 3);
    }
}


void Renderer::ReadMesh_(const std::string& mesh_path) {
    std::ifstream mesh_file;
    mesh_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        mesh_file.open(mesh_path);
        if (!mesh_file.is_open()) {
            std::cerr << "ERROR: Failed to open mesh file: " << mesh_path << std::endl;
        }

        // mesh_file >> vertex_count_;
        // vertices_ = new float[vertex_count_ * 3];
        // for (int i = 0; i < vertex_count_ * 3; i += 3) {
        //     mesh_file >> vertices_[i];
        //     mesh_file >> vertices_[i + 1];
        //     mesh_file >> vertices_[i + 2];
        // }

        // mesh_file >> triangle_count_;
        // indices_ = new uint[triangle_count_ * 3];
        // for (int i = 0; i < triangle_count_ * 3; i += 3) {
        //     mesh_file >> indices_[i];
        //     mesh_file >> indices_[i + 1];
        //     mesh_file >> indices_[i + 2];
        // }
        
        mesh_file >> triangle_count_;
        vertices_ = new float[triangle_count_ * 3 * 2 * 3];
        for (int i = 0; i < triangle_count_ * 3 * 2 * 3; i++) {
            mesh_file >> vertices_[i];
        }

    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR: Failed to read mesh file: " << mesh_path << std::endl;
    }
}


// void Renderer::CalculateNormals_() {
//     normals_ = new float[vertex_count_ * 3];
// 
//     for (int i = 0; i < triangle_count_ * 3; i += 3) {
//         uint v0 = indices_[i];
//         uint v1 = indices_[i + 1];
//         uint v2 = indices_[i + 2];
// 
//         glm::vec3 p0(vertices_[v0 * 3], vertices_[v0 * 3 + 1], vertices_[v0 * 3 + 2]);
//         glm::vec3 p1(vertices_[v1 * 3], vertices_[v1 * 3 + 1], vertices_[v1 * 3 + 2]);
//         glm::vec3 p2(vertices_[v2 * 3], vertices_[v2 * 3 + 1], vertices_[v2 * 3 + 2]);
// 
//         glm::vec3 edge1 = p1 - p0;
//         glm::vec3 edge2 = p2 - p0;
//         glm::vec3 face_normal = glm::normalize(glm::cross(edge2, edge1));
// 
//         normals_[v0 * 3] += face_normal.x;
//         normals_[v0 * 3 + 1] += face_normal.y;
//         normals_[v0 * 3 + 2] += face_normal.z;
// 
//         normals_[v1 * 3] += face_normal.x;
//         normals_[v1 * 3 + 1] += face_normal.y;
//         normals_[v1 * 3 + 2] += face_normal.z;
// 
//         normals_[v2 * 3] += face_normal.x;
//         normals_[v2 * 3 + 1] += face_normal.y;
//         normals_[v2 * 3 + 2] += face_normal.z;
//     }
// 
//     for (int i = 0; i < vertex_count_ * 3; i += 3) {
//         glm::vec3 normal(normals_[i], normals_[i + 1], normals_[i + 2]);
//         normal = glm::normalize(normal);
//         normals_[i] = normal.x;
//         normals_[i + 1] = normal.y;
//         normals_[i + 2] = normal.z;
//     }
// }


void Renderer::CreateBuffers_() {
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, triangle_count_ * 3 * 2 * 3 * sizeof(float), vertices_, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
