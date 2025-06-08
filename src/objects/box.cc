#include "objects/box.h"
#include "graphics/renderers/box_renderer.h"


Box::Box(glm::vec3 pos, glm::vec3 rot_axis, float rot_deg, glm::vec3 scale, BoxRenderer* renderer) : 
    pos_(pos), 
    rot_axis_(rot_axis), 
    rot_deg_(rot_deg),
    scale_(scale)
{
    renderer->emplace_box(this);
}


Box::~Box() {}
