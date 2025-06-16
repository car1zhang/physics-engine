#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "physics/types.h"


enum class BodyType {
    BOX
};


class GraphicsManager;
class Body;


class BodyManager {
public:
    BodyManager();
    ~BodyManager();

    Body* CreateBody(BodyType type, Physics::Vec3 pos, Physics::Vec3 rot_axis, float rot_deg, Physics::Vec3 scale, GraphicsManager* graphics_manager);
    void DestroyBody(unsigned int id, GraphicsManager* graphics_manager);

    void UpdateBodies(float dt);

    std::vector<Body*> get_bodies() { return bodies_; }

private:
    std::vector<Body*> bodies_;
};
