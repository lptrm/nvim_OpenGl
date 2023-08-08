#include "TestBatchRendering.h"

namespace test {
test::TestBatchRendering::TestBatchRendering()
    : m_Proj(glm::ortho(0.0f, 768.0f, 0.0f, 1024.0f, -1.0f, 1.0f)),
      m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
      m_TranslationA(0, 0, 0) {
  float positions[] = {
      -250.0f, -250.0f, 0.0f, 0.0f, // 0
      250.0f,  -250.0f, 1.0f, 0.0f, // 1
      250.0f,  250.0f,  1.0f, 1.0f, // 2
      -250.0f, 250.0f,  0.0f, 1.0f, // 3

      500.0f,  500.0f,  0.0f, 0.0f, // 4
      1000.0f, 500.0f,  1.0f, 0.0f, // 5
      1000.0f, 1000.0f, 1.0f, 1.0f, // 6
      500.0f,  1000.0f, 0.0f, 1.0f  // 7

  };
  unsigned int indices[] = {0, 1, 2, 0, 3, 2, 4, 5, 6, 4, 7, 6};
  GLCALL(glEnable(GL_BLEND));
  GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  m_VAO = std::make_unique<VertexArray>();

  // vertex buffer object
  m_VertexBuffer =
      std::make_unique<VertexBuffer>(positions, 8 * 4 * sizeof(float));

  // vertex buffer layout
  VertexBufferLayout layout;
  layout.Push<float>(2);
  layout.Push<float>(2);
  m_VAO->AddBuffer(*m_VertexBuffer, layout);
  m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);
  m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
  m_Shader->Bind();
  m_Texture = std::make_unique<Texture>("res/textures/texture.png");
  m_Shader->SetUniform1i("u_Texture", 0);
}
test::TestBatchRendering::~TestBatchRendering(){};

void test::TestBatchRendering::OnUpdate(float deltaTime) {}
void test::TestBatchRendering::OnRender() {
  GLCALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
  GLCALL(glClear(GL_COLOR_BUFFER_BIT));
  Renderer renderer;
  m_Texture->Bind();
  {
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
    glm::mat4 u_MVP = m_Proj * m_View * model;
    m_Shader->Bind();
    m_Shader->SetUniformMat4f("u_MVP", u_MVP);
    renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
  }
}
void test::TestBatchRendering::OnImGuiRender() {
  ImGui::SliderFloat3("logos", &m_TranslationA.x, 0.0f, 1080.0f);
}
} // namespace test
