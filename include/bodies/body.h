#pragma once

#include <glm/glm.hpp>

#include "bodies/body_manager.h"
#include "physics/types.h"


class Component;

class Body {
public:
    // Body() = default;
    Body(BodyType type, Physics::Vec3 pos, Physics::Vec3 rot_axis, float rot_deg, Physics::Vec3 scale);
    ~Body();

    void Update(float dt);
    void ApplyForce(Physics::Vec3 force);

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    unsigned int get_id() const { return id_; }
    BodyType get_type() const { return type_; }

    Physics::Vec3 get_pos() const { return pos_; }
    void set_pos(const Physics::Vec3 pos) { pos_ = pos; }
    Physics::Vec3 get_vel() const { return vel_; }
    void set_vel(const Physics::Vec3 vel) { vel_ = vel; }
    Physics::Vec3 get_accel() const { return accel_; }
    void set_accel(const Physics::Vec3 accel) { accel_ = accel; }

    Physics::Vec3 get_rot_axis() const { return rot_axis_; }
    float get_rot_deg() const { return rot_deg_; }
    void set_rot(const Physics::Vec3 axis, const float deg)  {
        rot_axis_ = axis;
        rot_deg_ = deg;
    }

    Physics::Vec3 get_scale() const { return scale_; }
    void set_scale(const Physics::Vec3 scale) { scale_ = scale; }

    float get_mass() const { return mass_; }
    void set_mass(const float mass) { mass_ = mass; }

private: 
    unsigned int id_;
    BodyType type_;

    Physics::Vec3 pos_;
    Physics::Vec3 vel_;
    Physics::Vec3 accel_;

    Physics::Vec3 rot_axis_;
    float rot_deg_;

    Physics::Vec3 scale_;

    float mass_; // TODO: density?

    std::vector<Component*> components_;
};
