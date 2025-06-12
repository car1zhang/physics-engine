#include "camera.h"
#include "constants.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


Camera::Camera(glm::vec3 pos, float yaw, float pitch, float fov, float speed, float mouse_sensitivity) : 
    world_up_(glm::vec3(0.0f, 1.0f, 0.0f)),
    pos_(pos),
    yaw_(yaw),
    pitch_(pitch),
    fov_(fov),
    speed_(speed),
    mouse_sensitivity_(mouse_sensitivity)
{
    CalculateVectors_();
}


Camera::~Camera() {}


void Camera::Update(float dt, Controller* const controller) {
    ProcessKeyboard_(dt, controller);
    ProcessMouse_(dt, controller);
    CalculateVectors_();
    CalculateMatrices_();
}


void Camera::ProcessKeyboard_(float dt, Controller* const controller) {
    if (controller->get_key_pressed(GLFW_KEY_W)) {
        pos_ += front_ * speed_ * dt;
    }
    if (controller->get_key_pressed(GLFW_KEY_S)) {
        pos_ -= front_ * speed_ * dt;
    }
    if (controller->get_key_pressed(GLFW_KEY_A)) {
        pos_ -= right_ * speed_ * dt;
    }
    if (controller->get_key_pressed(GLFW_KEY_D)) {
        pos_ += right_ * speed_ * dt;
    }
    if (controller->get_key_pressed(GLFW_KEY_SPACE)) {
        pos_ += up_ * speed_ * dt;
    }
    if (controller->get_key_pressed(GLFW_KEY_LEFT_CONTROL)) {
        pos_ -= up_ * speed_ * dt;
    }
}


void Camera::ProcessMouse_(float dt, Controller* const controller) { // TODO: zoom ?
    float x_offset = controller->get_x_cursor_offset() * mouse_sensitivity_;
    float y_offset = controller->get_y_cursor_offset() * mouse_sensitivity_;

    yaw_ += x_offset;
    pitch_ += y_offset;

    if (pitch_ > 89.0f) {
        pitch_ = 89.0f;
    }
    if (pitch_ < -89.0f) {
        pitch_ = -89.0f;
    }
}


void Camera::CalculateVectors_() {
    front_.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_.y = sin(glm::radians(pitch_));
    front_.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front_);
    right_ = glm::normalize(glm::cross(front_, world_up_));
    up_ = glm::normalize(glm::cross(right_, front_));
}


void Camera::CalculateMatrices_() {
    view_matrix_ = glm::lookAt(pos_, pos_ + front_, up_);

    projection_matrix_ = glm::perspective( // TODO: ortho camera?
        glm::radians(fov_),
        (float)constants::kWindowWidth / (float)constants::kWindowHeight,
        0.1f, 100.0f
    );
}
