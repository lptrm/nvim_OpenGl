#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader {
private:
  unsigned int m_RendererID;
  std::string m_FilePath;
  mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

public:
  Shader(const std::string &filepath);
  ~Shader();
  void Bind() const;
  void Unbind() const;
  // Set uniforms
  void SetUniform1i(const std::string &name, int value);
  void SetUniform1f(const std::string &name, float value);
  void SetUniform2f(const std::string &name, float v0, float v1);
  void SetUniform3f(const std::string &name, float v0, float v1, float v2);
  void SetUniform4f(const std::string &name, float v0, float v1, float v2,
                    float v3);
  void SetUniformMat3f(const std::string &name, const glm::mat3 &matrix);
  void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);

private:
  ShaderProgramSource ParseShader(const std::string &filepath);
  unsigned int CompileShader(unsigned int type, const std::string &source);
  unsigned int CreateShader(const std::string &vertexShader,
                            const std::string &fragmentShader);
  GLint GetUniformLocation(const std::string &name) const;
};
