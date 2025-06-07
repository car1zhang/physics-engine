#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

#include "graphics/shader.h"


Shader::Shader(const char* vertex_path, const char* fragment_path) {
    GLuint vertex_shader = LoadShader_(vertex_path, GL_VERTEX_SHADER); // relocate files later
    GLuint fragment_shader = LoadShader_(fragment_path, GL_FRAGMENT_SHADER);

    int success;
    char info_log[512];
    id_ = glCreateProgram();
    glAttachShader(id_, vertex_shader);
    glAttachShader(id_, fragment_shader);
    glLinkProgram(id_);
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id_, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to link shader program\n" << info_log << std::endl;
    }
    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);
}


Shader::~Shader() {
    glDeleteProgram(id_);
}


void Shader::Use() {
    glUseProgram(id_);
}


void Shader::SetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value); 
}

void Shader::SetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value); 
}

void Shader::SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value); 
}

void Shader::SetVector2(const std::string &name, float v1, float v2) const {
    glUniform2f(glGetUniformLocation(id_, name.c_str()), v1, v2); 
}

void Shader::SetVector3(const std::string &name, float v1, float v2, float v3) const {
    glUniform3f(glGetUniformLocation(id_, name.c_str()), v1, v2, v3); 
}

void Shader::SetVector4(const std::string &name, float v1, float v2, float v3, float v4) const {
    glUniform4f(glGetUniformLocation(id_, name.c_str()), v1, v2, v3, v4);
}

void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


GLuint Shader::LoadShader_(const std::string& filepath, GLenum shader_type) {
    std::ifstream shader_file;
    std::stringstream shader_stream;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shader_file.open(filepath);
        shader_stream << shader_file.rdbuf();
        shader_file.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "ERROR: Failed to read shader file: " << filepath << std::endl;
    }
    std::string shader_string = shader_stream.str();
    const char* shader_source = shader_string.c_str(); // necessary bc of some memory copy quirk

    int success;
    char info_log[512];
    unsigned int shader;
    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cerr << "ERROR: Failed to compile shader\n" << info_log << std::endl;
        return 0;
    }

    return shader;
}
