#pragma once
#include <GLFW/glfw3.h>
#include "graphics_manager.h"

class Simulation {
public:
    Simulation();
    ~Simulation();
    void RunLoop();

private:
    void ProcessInput_();
    void UpdateState_(double delta_time);
    void RenderOutput_();

    GraphicsManager* graphics_manager_;

    bool is_running_;
};
