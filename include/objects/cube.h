#pragma once

#include <glm/glm.hpp>


class CubeRenderer;

class Cube {
public:
    Cube(glm::vec3 pos, glm::vec3 rot_axis, float rot_deg, float scale, CubeRenderer* renderer);
    ~Cube();

    glm::vec3 get_pos() const { return pos_; }
    glm::vec3 get_rot_axis() const { return rot_axis_; }
    float get_rot_deg() const { return rot_deg_; }
    float get_scale() const { return scale_; }

private: // TODO: convert to be physics types
    glm::vec3 pos_;
    glm::vec3 rot_axis_;
    float rot_deg_;
    float scale_;
};
