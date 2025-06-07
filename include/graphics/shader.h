#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader(const char* vertex_path, const char* fragment_path);
    ~Shader();

    void Use();

    // you gotta use the program before using these
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetVector2(const std::string &name, float v1, float v2) const;
    void SetVector3(const std::string &name, float v1, float v2, float v3) const;
    void SetVector4(const std::string &name, float v1, float v2, float v3, float v4) const;
    void SetMat2(const std::string &name, const glm::mat2 &mat) const;
    void SetMat3(const std::string &name, const glm::mat3 &mat) const;
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;

    GLuint get_id() { return id_; }

private:
    GLuint LoadShader_(const std::string& filepath, GLenum shader_type);

    GLuint id_;
};
