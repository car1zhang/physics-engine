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

    camera_ = new Camera(glm::vec3(0.0f, 0.0f, 10.0f), -90.0f, 0.0f, 45.0f, 3.0f, 0.05f, controller_);
    graphics_manager_->set_camera(camera_);

    cubes_ = {
        new Cube(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.1f, 1.0f, 0.3f), 0.0f,
            1.5f,
            graphics_manager_->get_cube_renderer()
        ),
        new Cube(
            glm::vec3(7.1f, 0.3f, -15.0f),
            glm::vec3(-0.3f, 0.2f, -0.5f), 0.0f,
            1.0f,
            graphics_manager_->get_cube_renderer()
        ),
        new Cube(
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(1.0f, 0.3f, -0.5f), 0.0f,
            1.2f,
            graphics_manager_->get_cube_renderer()
        ),
        new Cube(
            glm::vec3(-3.8f, 3.0f, -10.3f),
            glm::vec3(0.2f, -1.0f, 0.5f), 0.0f,
            0.5f,
            graphics_manager_->get_cube_renderer()
        ),
        new Cube(
            glm::vec3(0.8f, 1.0f, -2.2f),
            glm::vec3(-0.8, -0.9, 1.0), 0.0f,
            0.8f,
            graphics_manager_->get_cube_renderer()
        ),
    };

    is_running_ = true;

    prev_time_ = glfwGetTime();
}


Simulation::~Simulation() {
    std::cout << "Shutting down" << std::endl;

    delete graphics_manager_;

    for (Cube* cube : cubes_) {
        delete cube;
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
    if (glfwWindowShouldClose(graphics_manager_->get_window()) || controller_->get_key_pressed(GLFW_KEY_ESCAPE)) {
        is_running_ = false;
    }
}


void Simulation::UpdateState_() {
    while (glfwGetTime() < prev_time_ + constants::kTargetFrameTime) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    float delta_time = glfwGetTime() - prev_time_;
    prev_time_ = glfwGetTime();

    camera_->Update(delta_time);
}


void Simulation::RenderOutput_() {
    graphics_manager_->Draw();
}
