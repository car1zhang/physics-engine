#pragma once

#include <vector>

#include <glm/glm.hpp>


enum class BodyType {
    BOX
};


class GraphicsManager;
class Body;


class BodyManager {
public:
    BodyManager();
    ~BodyManager();

    void CreateBody(BodyType type, glm::vec3 pos, glm::vec3 rot_axis, float rot_deg, glm::vec3 scale, GraphicsManager* graphics_manager);
    void DestroyBody(unsigned int id, GraphicsManager* graphics_manager);

    void UpdateBodies(float dt);

private:
    std::vector<Body*> bodies_;
};
