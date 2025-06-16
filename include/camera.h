#pragma once

#include <glm/glm.hpp>

#include "controller.h"


class Camera {
public:
    Camera();
    Camera(glm::vec3 pos, float yaw, float pitch, float fov, float speed, float mouse_sensitivity);
    ~Camera();

    void Update(float delta_time, Controller* const controller);

    glm::vec3 get_pos() const { return pos_; }
    glm::vec3 get_front() const { return front_; }
    glm::mat4 get_view_matrix() const { return view_matrix_; }
    glm::mat4 get_projection_matrix() const { return projection_matrix_; }

private: // TODO: should be physics vectors too
    void ProcessKeyboard_(float dt, Controller* const controller);
    void ProcessMouse_(float dt, Controller* const controller);
    void CalculateVectors_();
    void CalculateMatrices_();

    glm::vec3 world_up_;

    glm::vec3 pos_;

    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    float yaw_;
    float pitch_;

    float fov_;
    float speed_;
    float mouse_sensitivity_;

    glm::mat4 view_matrix_;
    glm::mat4 projection_matrix_;
};
