#include "bodies/body.h"


Body::Body(BodyType type, glm::vec3 pos, glm::vec3 rot_axis, float rot_deg, glm::vec3 scale) : 
    type_(type),
    pos_(pos), 
    rot_axis_(rot_axis), 
    rot_deg_(rot_deg),
    scale_(scale)
{}


Body::~Body() {}


void Body::Update(float dt) {
    rot_deg_ += dt * 10.0f;
}
