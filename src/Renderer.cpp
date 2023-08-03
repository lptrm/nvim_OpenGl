#include "Renderer.h"
#include <gl/glew.h>
#include <iostream>


void GLClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool GLLogCall(const char *function, const char *file, int line) {
  // get error code
  while (GLenum error = glGetError()) {
    // translate error code to string based on glew header file
    std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file
              << ":" << line << std::endl;
    return false;
  }
  return true;
}

void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT); }
void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib,
                    const Shader &shader) const {
  shader.Bind();
  va.Bind();
  ib.Bind();
  GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
