#include "bodies/body_manager.h"
#include "bodies/body.h"
#include "graphics/graphics_manager.h"


BodyManager::BodyManager() {}


BodyManager::~BodyManager() {
    for (Body* body : bodies_) {
        delete body;
    }
}


Body* BodyManager::CreateBody(BodyType type, Physics::Vec3 pos, Physics::Vec3 rot_axis, float rot_deg, Physics::Vec3 scale, GraphicsManager* graphics_manager) {
    Body* body = new Body(type, pos, rot_axis, rot_deg, scale);
    bodies_.emplace_back(body);

    switch (type) {
        case BodyType::BOX:
            graphics_manager->get_renderer(BodyType::BOX)->emplace_body(body);
            break;
    }

    return body;
}


void BodyManager::DestroyBody(unsigned int id, GraphicsManager* graphics_manager) {
    delete bodies_[id];
    bodies_.erase(std::find(bodies_.begin(), bodies_.end(), bodies_[id]));
    graphics_manager->get_renderer(bodies_[id]->get_type())->remove_body(bodies_[id]);
}


void BodyManager::UpdateBodies(float dt) {
    for (Body* body : bodies_) {
        body->Update(dt);
    }
}
