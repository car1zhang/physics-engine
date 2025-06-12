#pragma once

#include <glm/glm.hpp>

#include "bodies/body_manager.h"


class Body {
public:
    Body() = default;
    Body(BodyType type, glm::vec3 pos, glm::vec3 rot_axis, float rot_deg, glm::vec3 scale);
    ~Body();

    void Update(float dt);

    unsigned int get_id() const { return id_; }
    BodyType get_type() const { return type_; }
    glm::vec3 get_pos() const { return pos_; }
    glm::vec3 get_rot_axis() const { return rot_axis_; }
    float get_rot_deg() const { return rot_deg_; }
    glm::vec3 get_scale() const { return scale_; }

private: // TODO: convert to be physics types
    unsigned int id_;
    BodyType type_;

    glm::vec3 pos_;
    glm::vec3 rot_axis_;
    float rot_deg_;
    glm::vec3 scale_;
};
