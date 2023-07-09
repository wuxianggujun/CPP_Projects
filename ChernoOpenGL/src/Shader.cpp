//
// Created by WuXiangGuJun on 2023/7/9.
//
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"


Shader::Shader(const std::string &filePath) : m_FilePath(filePath), m_RendererID(0) {
    ShaderProgramSource sources = ParseShader(filePath);
    m_RendererID = CreateShader(sources.VertexShaderSource, sources.FragmentShaderSource);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const std::string &filePath) {
    std::ifstream fileStream(filePath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(fileStream, line)) {
        if (line.find("#shader") != std::string::npos) {
            //如果是找到了顶点着色器
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
                //如歌是找到了片段着色器
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        } else {
            if (type == ShaderType::NONE)
                throw std::runtime_error("No shader type found");
            ss[(int) type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!"
                  << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
};

void Shader::Bind() const {
    glUseProgram(m_RendererID);

}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetUniform1f(const std::string &name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

unsigned int Shader::GetUniformLocation(const std::string &name) {

    if (m_UniformLocations.find(name) != m_UniformLocations.end()) {
        return m_UniformLocations[name];
    }
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' not found in shader!" << std::endl;
    m_UniformLocations[name] = location;

    return location;
}
