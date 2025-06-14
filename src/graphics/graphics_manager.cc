#include "graphics/graphics_manager.h"
#include "constants.h"


GraphicsManager::GraphicsManager() : 
    shader_(Shader(constants::kVertexShaderPath, constants::kFragmentShaderPath))
{
    shader_.Use();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    renderers_[BodyType::BOX] = new Renderer(constants::kBoxMeshPath);
}


GraphicsManager::~GraphicsManager() {
    for (auto const& [type, renderer] : renderers_) {
        delete renderer;
    }
    renderers_.clear();
}


void GraphicsManager::Draw(Camera* camera, GLFWwindow* window) {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_.SetMat4("view", camera->get_view_matrix());
    shader_.SetMat4("projection", camera->get_projection_matrix());

    shader_.SetFloat("ambientStrength", 0.2f);
    shader_.SetFloat("specularStrength", 0.8f);

    shader_.SetVector3("lightColor", 0.8f, 0.8f, 0.8f);
    shader_.SetVector3("lightPos", -30.0f, 20.0f, -10.0f); // TODO: make this an object or smth

    shader_.SetVector3("objectColor", 1.0f, 0.5f, 0.3f);

    shader_.SetVector3("viewPos", camera->get_pos().x, camera->get_pos().y, camera->get_pos().z);

    for (auto const& [type, renderer] : renderers_) {
        renderer->DrawBodies(&shader_);
    }

    glfwSwapBuffers(window);
}

