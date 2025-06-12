#pragma once

#include <GLFW/glfw3.h>


class Controller {
public:
    Controller();
    ~Controller();

    void UpdateInput(GLFWwindow* const window);
    
    bool get_key_pressed(int key) const { return keyboard_state_[key]; }
    bool get_key_just_pressed(int key) const { return keyboard_state_[key] && !prev_keyboard_state_[key]; }
    float get_x_cursor_offset() const { return x_cursor_offset_; }
    float get_y_cursor_offset() const { return y_cursor_offset_; }

private:
    bool keyboard_state_[GLFW_KEY_LAST];
    bool prev_keyboard_state_[GLFW_KEY_LAST];

    float x_cursor_offset_;
    float y_cursor_offset_;
    float prev_cursor_x_;
    float prev_cursor_y_;

    bool is_first_frame_;
};
