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
}


void GraphicsManager::Draw(Camera* camera, GLFWwindow* window) {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_.SetMat4("view", camera->get_view_matrix());
    shader_.SetMat4("projection", camera->get_projection_matrix());

    shader_.SetFloat("ambientStrength", 0.2f);
    shader_.SetVector3("lightColor", 1.0f, 1.0f, 1.0f);
    shader_.SetVector3("objectColor", 1.0f, 1.0f, 1.0f);

    for (auto const& [type, renderer] : renderers_) {
        renderer->DrawBodies(&shader_);
    }

    glfwSwapBuffers(window);
}

