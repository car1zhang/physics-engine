#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <graphics/renderers/cube_renderer.h>

#include "objects/cube.h"
#include "graphics/shader.h"


CubeRenderer::CubeRenderer() {
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}


CubeRenderer::~CubeRenderer() { // be sure to delete the cubes elsewhere
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
}


void CubeRenderer::DrawCubes(Shader* shader) {
    glBindVertexArray(vao_);

    for (Cube* cube : cubes_) {
        glm::mat4 model_matrix = glm::mat4(1.0f);

        model_matrix = glm::translate(model_matrix, cube->get_pos());

        float rot_deg = cube->get_rot_deg() + glfwGetTime() * 10.0f; // spinning
        model_matrix = glm::rotate(model_matrix, glm::radians(rot_deg), cube->get_rot_axis());

        model_matrix = glm::scale(model_matrix, glm::vec3(cube->get_scale(), cube->get_scale(), cube->get_scale()));

        shader->SetMat4("model", model_matrix);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}
