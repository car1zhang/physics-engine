#include "bodies/body.h"
#include "physics/components/component.h"

Body::Body(BodyType type, Physics::Vec3 pos, Physics::Vec3 rot_axis, float rot_deg, Physics::Vec3 scale) : 
    type_(type),
    pos_(pos), 
    rot_axis_(rot_axis), 
    rot_deg_(rot_deg),
    scale_(scale),
    mass_(1.0f)
{}


Body::~Body() {}


void Body::Update(float dt) {
    for (auto component : components_) {
        component->Update(dt);
    }
    vel_ = vel_ + accel_ * dt;
    pos_ = pos_ + vel_ * dt;
    if (vel_.magnitude() > 50.0f) {
        vel_ = vel_.normalize() * 50.0f;
    }
}

void Body::ApplyForce(Physics::Vec3 force) {
    accel_ = accel_ + force / mass_;
}


void Body::AddComponent(Component* component) {
    components_.emplace_back(component);
    component->set_body(this);
}


void Body::RemoveComponent(Component* component) {
    components_.erase(std::find(components_.begin(), components_.end(), component));
    component->set_body(nullptr);
}
