#pragma once

#include <glm/glm.hpp>


class BoxRenderer;

class Box {
public:
    Box(glm::vec3 pos, glm::vec3 rot_axis, float rot_deg, glm::vec3 scale, BoxRenderer* renderer);
    ~Box();

    void Update(float dt);

    glm::vec3 get_pos() const { return pos_; }
    glm::vec3 get_rot_axis() const { return rot_axis_; }
    float get_rot_deg() const { return rot_deg_; }
    glm::vec3 get_scale() const { return scale_; }

private: // TODO: convert to be physics types
    glm::vec3 pos_;
    glm::vec3 rot_axis_;
    float rot_deg_;
    glm::vec3 scale_;
};
