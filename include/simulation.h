#pragma once
#include <GLFW/glfw3.h>

class Simulation
{
    public:
        Simulation();
        ~Simulation();
        void run_loop();

        GLFWwindow* get_window() { return window; }

    private:
        void process_input();
        void update_state(double delta_time);
        void render_output();

        unsigned int shader_program, vao, vbo, ebo;

        GLFWwindow* window;

        bool is_running;
};
