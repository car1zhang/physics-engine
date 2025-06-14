#include "bodies/body.h"


Body::Body(BodyType type, Physics::Vec3 pos, Physics::Vec3 rot_axis, float rot_deg, Physics::Vec3 scale) : 
    type_(type),
    pos_(pos), 
    rot_axis_(rot_axis), 
    rot_deg_(rot_deg),
    scale_(scale)
{}


Body::~Body() {}


void Body::Update(float dt) {
    for (auto component : components_) {
        component->Update(dt);
    }
    vel_ = vel_ + accel_ * dt;
    pos_ = pos_ + vel_ * dt;
}
