#pragma once


namespace constants {
    constexpr int kWindowWidth = 800;
    constexpr int kWindowHeight = 600;
    constexpr double kTargetFrameTime = 1.0 / 60.0;
    constexpr const char* kProgramName = "Carl's Physics Engine";
    constexpr const char* kVertexShaderPath = "../shaders/vertex.glsl"; // TODO: these paths should not be relative in production
    constexpr const char* kFragmentShaderPath = "../shaders/fragment.glsl";
}
