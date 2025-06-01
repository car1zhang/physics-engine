#define GLFW_INCLUDE_NONE
#include <iostream>
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "simulation.h"
#include "constants.h"

Simulation::Simulation()
{
    std::cout << "Initializing simulation" << std::endl;

    /*map = new Map();*/

    if (!glfwInit())
    {
        std::cerr << "ERROR: Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(800, 600, "traffik", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);  // Get actual framebuffer size
    glViewport(0, 0, width, height);

    int success;
    char info_log[512];

    const char* vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to compile vertex shader\n" << info_log << std::endl;
    }

    const char* fragment_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to compile fragment shader\n" << info_log << std::endl;
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to link shader program\n" << info_log << std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    float ndc_vertices[] = {
        -0.5f, 0.5f, 0.0f,
        -0.8f, -0.5f, 0.0f,
        -0.2f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.2f, -0.5f, 0.0f,
        0.8f, -0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        3, 4, 5
    };
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ndc_vertices), ndc_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    is_running = true;
}

Simulation::~Simulation()
{
    std::cout << "Closing down shop" << std::endl;

    glfwDestroyWindow(window);
    glfwTerminate();

    /*delete map;*/

    is_running = false;
}

void Simulation::run_loop()
{
    using clock = std::chrono::high_resolution_clock;
    clock::time_point last_time = clock::now();

    while (is_running && !glfwWindowShouldClose(window))
    {
        process_input();

        // calculate delta time
        clock::time_point current_time = clock::now();
        std::chrono::duration<double> delta_time = current_time - last_time;
        last_time = current_time;
        update_state(delta_time.count());

        render_output();

        // 30 fps
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
}

void Simulation::process_input()
{
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        is_running = false;
    }
}

void Simulation::update_state(double delta_time)
{
}

void Simulation::render_output()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
}
