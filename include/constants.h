#pragma once


namespace constants {
    constexpr int kWindowWidth = 1280;
    constexpr int kWindowHeight = 720;

    constexpr double kTargetFrameTime = 1.0 / 120.0;

    constexpr const char* kProgramName = "Carl's Physics Engine";

    constexpr const char* kVertexShaderPath = "../shaders/vertex.glsl"; // TODO: these paths should not be relative in production
    constexpr const char* kFragmentShaderPath = "../shaders/fragment.glsl";

    constexpr const char* kBoxMeshPath = "../meshes/box.txt";

    constexpr float kGravity = 9.81f;
}
