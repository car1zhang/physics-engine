#include <string.h>

#include "controller.h"

#include <GLFW/glfw3.h>


Controller::Controller(GLFWwindow* const window) : 
    window_(window),
    x_cursor_offset_(0.0f),
    y_cursor_offset_(0.0f),
    prev_cursor_x_(0.0f),
    prev_cursor_y_(0.0f),
    is_first_frame_(true)
{
    memset(keyboard_state_, 0, GLFW_KEY_LAST);
    memset(prev_keyboard_state_, 0, GLFW_KEY_LAST);
}


Controller::~Controller() {}


void Controller::UpdateInput() {
    glfwPollEvents();
    
    for (int i = 0; i < GLFW_KEY_LAST; i++) {
        prev_keyboard_state_[i] = keyboard_state_[i];
        keyboard_state_[i] = glfwGetKey(window_, i) == GLFW_PRESS;
    }

    double xpos, ypos;
    glfwGetCursorPos(window_, &xpos, &ypos);
    if (!is_first_frame_) {
        x_cursor_offset_ = xpos - prev_cursor_x_;
        y_cursor_offset_ = prev_cursor_y_ - ypos;
    }
    prev_cursor_x_ = xpos;
    prev_cursor_y_ = ypos;
    is_first_frame_ = false;

    double scrollpos;
}
