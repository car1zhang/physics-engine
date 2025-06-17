#include "physics/components/gravity_component.h"
#include "constants.h"

void GravityComponent::Update(float dt) {
    body_->ApplyForce(Physics::Vec3(0.0f, -constants::kGravity, 0.0f) * body_->get_mass() * dt);
}
