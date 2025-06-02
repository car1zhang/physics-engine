#include <GLFW/glfw3.h>
#include <string>

class GraphicsManager {
public:
    GraphicsManager();
    ~GraphicsManager();

    void Draw();

    GLFWwindow* get_window() { return window_; }

private:
    void CreateWindow_();
    void InitializeShaders_();
    unsigned int LoadShader_(const std::string& filepath, GLenum shader_type);

    GLFWwindow* window_;

    unsigned int shader_program_, vao_, vbo_, ebo_;
};
