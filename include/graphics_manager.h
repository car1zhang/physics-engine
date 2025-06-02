#include <GLFW/glfw3.h>

class GraphicsManager {
public:
    GraphicsManager();
    ~GraphicsManager();

    void Draw();

    GLFWwindow* get_window() { return window_; }

private:
    GLFWwindow* window_;

    unsigned int shader_program_, vao_, vbo_, ebo_;
};
