#pragma once

#include "objects/cube.h"
#include "graphics/shader.h"

#include <glad/glad.h>
#include <vector>


class CubeRenderer { // TODO: make an abstract parent when adding other objects
public:
    CubeRenderer();
    ~CubeRenderer();

    void DrawCubes(Shader* shader);

    void emplace_cube(Cube* cube) { cubes_.emplace_back(cube); }
    void remove_cube(Cube* cube) { cubes_.erase(std::find(cubes_.begin(), cubes_.end(), cube)); } // TODO: learn to use smart pointers

private:
    std::vector<Cube*> cubes_;

    GLuint vao_, vbo_, ebo_;

    float vertices_[24] = {
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
    };
    uint indices_[36] = {
        0, 1, 2,
        1, 2, 4,

        0, 2, 3,
        2, 3, 5,

        0, 1, 3,
        1, 3, 6,

        4, 6, 7,
        1, 4, 6,

        5, 6, 7,
        3, 5, 6,

        4, 5, 7,
        2, 4, 5,
    };
};
