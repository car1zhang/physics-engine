#include "objects/cube.h"
#include "graphics/renderers/cube_renderer.h"


Cube::Cube(glm::vec3 pos, glm::vec3 rot_axis, float rot_deg, float scale, CubeRenderer* renderer) : 
    pos_(pos), 
    rot_axis_(rot_axis), 
    rot_deg_(rot_deg),
    scale_(scale)
{
    renderer->emplace_cube(this);
}


Cube::~Cube() {}
