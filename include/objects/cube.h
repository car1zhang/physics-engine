#pragma once

#include <glm/glm.hpp>


class CubeRenderer;

class Cube {
public:
    Cube(glm::vec3 pos, glm::vec3 rot_axis, float rot_deg, float scale, CubeRenderer* renderer);
    ~Cube();

    glm::vec3 get_pos() const { return pos; }
    glm::vec3 get_rot_axis() const { return rot_axis; }
    float get_rot_deg() const { return rot_deg; }
    float get_scale() const { return scale; }

private: // TODO: convert to be physics types
    glm::vec3 pos;
    glm::vec3 rot_axis;
    float rot_deg;
    float scale;
};
