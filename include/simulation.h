#pragma once

#include "graphics/graphics_manager.h"
#include "bodies/body_manager.h"
#include "camera.h"
#include "controller.h"

#include <GLFW/glfw3.h>


class Simulation {
public:
    Simulation();
    ~Simulation();
    void RunLoop();

private:
    void CreateWindow_();
    GLFWwindow* window_;

    void ProcessInput_();
    void UpdateState_();
    void RenderOutput_();

    std::unique_ptr<GraphicsManager> graphics_manager_;
    BodyManager body_manager_;
    Camera camera_;
    Controller controller_;

    bool is_running_;
    bool is_paused_;
    float prev_time_;
};
