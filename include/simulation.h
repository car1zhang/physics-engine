#pragma once

#include "graphics/graphics_manager.h"
#include "graphics/camera.h"
#include "controller.h"

#include <GLFW/glfw3.h>


class Simulation {
public:
    Simulation();
    ~Simulation();
    void RunLoop();

private:
    void ProcessInput_();
    void UpdateState_();
    void RenderOutput_();

    Controller* controller_;
    GraphicsManager* graphics_manager_;
    Camera* camera_;

    bool is_running_;
    float prev_time_;

    std::vector<Box*> boxes_;
};
