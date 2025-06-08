#pragma once

#include "objects/box.h"
#include "graphics/shader.h"

#include <glad/glad.h>
#include <vector>


class BoxRenderer { // TODO: make an abstract parent when adding other objects
public:
    BoxRenderer();
    ~BoxRenderer();

    void DrawBoxes(Shader* shader);

    void emplace_box(Box* box) { boxes_.emplace_back(box); }
    void remove_box(Box* box) { boxes_.erase(std::find(boxes_.begin(), boxes_.end(), box)); } // TODO: learn to use smart pointers

private:
    std::vector<Box*> boxes_;

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
