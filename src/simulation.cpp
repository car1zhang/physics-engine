#define GLFW_INCLUDE_NONE
#include <iostream>
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "simulation.h"

Simulation::Simulation() {
    std::cout << "Initializing simulation" << std::endl;

    if (!glfwInit()) {
        std::cerr << "ERROR: Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    graphics_manager_ = new GraphicsManager();

    is_running_ = true;
}

Simulation::~Simulation() {
    std::cout << "Closing down shop" << std::endl;

    delete graphics_manager_;

    is_running_ = false;
}

void Simulation::RunLoop() {
    using clock = std::chrono::high_resolution_clock;
    clock::time_point last_time = clock::now();

    while (is_running_) {
        ProcessInput_();

        // calculate delta time
        clock::time_point current_time = clock::now();
        std::chrono::duration<double> delta_time = current_time - last_time;
        last_time = current_time;
        UpdateState_(delta_time.count());

        RenderOutput_();

        // 30 fps
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
}

void Simulation::ProcessInput_() {
    glfwPollEvents();
    if (
        glfwGetKey(graphics_manager_->get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS || 
        glfwWindowShouldClose(graphics_manager_->get_window())
    ) {
        is_running_ = false;
    }
}

void Simulation::UpdateState_(double delta_time) {
}

void Simulation::RenderOutput_() {
    graphics_manager_->Draw();
}
