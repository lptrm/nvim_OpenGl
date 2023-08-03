#pragma once

#include "IndexBuffer.h"
#include <gl/glew.h>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"


#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    __debugbreak();
#define GLCALL(x)                                                              \
  GLClearError();                                                              \
  x;                                                                           \
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);
class Renderer {
public:
  void Clear() const;
  void Draw(const VertexArray &va, const IndexBuffer &ib,
            const Shader &shader) const;
};
