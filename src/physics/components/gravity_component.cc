#include "physics/components/gravity_component.h"
#include "constants.h"
#include <iostream>

GravityComponent::GravityComponent(BodyManager* body_manager) : body_manager_(body_manager) {}

void GravityComponent::Update(float dt) {
    // body_->ApplyForce(Physics::Vec3(0.0f, -constants::kGravity, 0.0f) * body_->get_mass() * dt);
    for (Body* other_body : body_manager_->get_bodies()) {
        if (other_body == body_) { // TODO: check if there is a gravity component on the other body
            continue;
        }

        Physics::Vec3 rel_pos = other_body->get_pos() - body_->get_pos();
        Physics::Vec3 force = rel_pos * constants::kGravitationalConstant * other_body->get_mass() * body_->get_mass() / rel_pos.magnitude();

        body_->ApplyForce(force * dt);
    }
}
