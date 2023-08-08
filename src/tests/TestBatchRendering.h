#pragma once

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Test.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include <memory>

namespace test {
class TestBatchRendering : public Test {
private:
  std::unique_ptr<VertexArray> m_VAO;
  std::unique_ptr<IndexBuffer> m_IndexBuffer;
  std::unique_ptr<Shader> m_Shader;
  std::unique_ptr<Texture> m_Texture;
  std::unique_ptr<VertexBuffer> m_VertexBuffer;

  glm::mat4 m_Proj, m_View;
  glm::vec3 m_TranslationA;

public:
  TestBatchRendering();
  ~TestBatchRendering();
  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};
} // namespace test
