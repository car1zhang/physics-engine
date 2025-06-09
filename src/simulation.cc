#define GLFW_INCLUDE_NONE

#include <iostream>
#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "simulation.h"
#include "constants.h"


Simulation::Simulation() {
    std::cout << "Initializing simulation" << std::endl;

    if (!glfwInit()) {
        std::cerr << "ERROR: Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    graphics_manager_ = new GraphicsManager();

    controller_ = new Controller(graphics_manager_->get_window());

    camera_ = new Camera(
        glm::vec3(0.0f, 0.0f, 0.0f), // pos
        0.0f, 0.0f, // rot
        45.0f, // fov
        3.0f, // speed
        0.05f, // sens
        controller_ // controller
    );
    graphics_manager_->set_camera(camera_);

    boxes_ = {
        new Box(
            glm::vec3(3.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f), 0.0f,
            glm::vec3(1.0f, 2.0f, 1.0f),
            graphics_manager_->get_box_renderer()
        )
    };

    is_running_ = true;
    is_paused_ = false;

    prev_time_ = glfwGetTime();
}


Simulation::~Simulation() {
    std::cout << "Shutting down" << std::endl;

    delete graphics_manager_;

    for (Box* box : boxes_) {
        delete box;
    }

    is_running_ = false;
}


void Simulation::RunLoop() {
    while (is_running_) {
        ProcessInput_();
        UpdateState_();
        RenderOutput_();
    }
}


void Simulation::ProcessInput_() {
    controller_->UpdateInput();
    
    if (glfwWindowShouldClose(graphics_manager_->get_window())) {
        is_running_ = false;
    }
    
    if (controller_->get_key_just_pressed(GLFW_KEY_ESCAPE)) {
        is_paused_ = !is_paused_;
        
        if (is_paused_) {
            glfwSetInputMode(graphics_manager_->get_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(graphics_manager_->get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}


void Simulation::UpdateState_() {
    while (glfwGetTime() < prev_time_ + constants::kTargetFrameTime) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    float dt = glfwGetTime() - prev_time_;
    prev_time_ = glfwGetTime();

    if (!is_paused_) {
        camera_->Update(dt);
        for (Box* box : boxes_) {
            box->Update(dt);
        }
    }
}


void Simulation::RenderOutput_() {
    graphics_manager_->Draw();
}
