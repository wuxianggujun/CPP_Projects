//
// Created by WuXiangGuJun on 2023/7/9.
//
#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource {
    std::string VertexShaderSource;
    std::string FragmentShaderSource;
};

class Shader {
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocations;

public:
    Shader(const std::string &filePath);

    ~Shader();

    void Bind() const;

    void Unbind() const;

    //Set uniforms
    void SetUniform1f(const std::string &name, float value);
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);


private:
    ShaderProgramSource ParseShader(const std::string &filePath);

    unsigned int CompileShader(unsigned int type, const std::string &source);

    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

    unsigned int GetUniformLocation(const std::string &name);

};