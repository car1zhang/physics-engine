#define GLFW_INCLUDE_NONE

#include <iostream>
#include <chrono>
#include <thread>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "simulation.h"
#include "objects/cube.h"


Simulation::Simulation() {
    std::cout << "Initializing simulation" << std::endl;

    if (!glfwInit()) {
        std::cerr << "ERROR: Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    graphics_manager_ = new GraphicsManager();

    cubes_ = {
        new Cube(
            glm::vec3(0.0f, 0.0f, -2.0f),
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
