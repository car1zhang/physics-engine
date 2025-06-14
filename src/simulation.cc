#include <iostream>
#include <thread>

#include <glad/glad.h>

#include "simulation.h"
#include "constants.h"


Simulation::Simulation() {
    std::cout << "Initializing simulation" << std::endl;

    if (!glfwInit()) {
        std::cerr << "ERROR: Failed to initialize GLFW" << std::endl;
        exit(-1);
    }
    CreateWindow_();

    graphics_manager_ = std::make_unique<GraphicsManager>(); // smart pointer since must wait for glfw to init

    body_manager_ = BodyManager();

    camera_ = Camera();

    controller_ = Controller();

    body_manager_.CreateBody(BodyType::BOX, Physics::Vec3(3.0f, 0.0f, 0.0f), Physics::Vec3(0.0f, 1.0f, 0.0f), 0.0f, Physics::Vec3(1.0f, 1.0f, 1.0f), graphics_manager_.get()); // hardcoded - move to file?

    is_running_ = true;
    is_paused_ = false;

    prev_time_ = glfwGetTime();
}


Simulation::~Simulation() {
    std::cout << "Shutting down" << std::endl;
    is_running_ = false;
    glfwDestroyWindow(window_);
    glfwTerminate();
}


void Simulation::RunLoop() {
    while (is_running_) {
        ProcessInput_();
        UpdateState_();
        RenderOutput_();
    }
}


void Simulation::CreateWindow_() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window_ = glfwCreateWindow(constants::kWindowWidth, constants::kWindowHeight, constants::kProgramName, nullptr, nullptr);
    if (!window_) {
        std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window_);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);
}


void Simulation::ProcessInput_() {
    controller_.UpdateInput(window_);
    
    if (glfwWindowShouldClose(window_)) {
        is_running_ = false;
    }
    
    if (controller_.get_key_just_pressed(GLFW_KEY_ESCAPE)) {
        is_paused_ = !is_paused_;
        
        if (is_paused_) {
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}


void Simulation::UpdateState_() {
    while (glfwGetTime() < prev_time_ + constants::kTargetFrameTime) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    float dt = glfwGetTime() - prev_time_;
    prev_time_ = glfwGetTime();

    if (is_paused_) {
        return;
    }
    camera_.Update(dt, &controller_);
    body_manager_.UpdateBodies(dt);
}


void Simulation::RenderOutput_() {
    graphics_manager_->Draw(&camera_, window_);
}
