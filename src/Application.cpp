// for opengl function calls
#include <GL/glew.h>
// for easy window creation
#include <GLFW/glfw3.h>
#include <filesystem>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
// for input
#include <iostream>
//
#include <fstream>
//
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <sstream>

void ClearAll() {
  GLCALL(glUseProgram(0));
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
  GLCALL(glBindVertexArray(0));
}

int main(void) {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  // sync framerate with monitor refresh rate
  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK)
    std::cout << "Error" << std::endl;

  std::cout << glGetString(GL_VERSION) << std::endl;
  { // scope for clearing stack allocated buffers
    // vertex positions
    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f,  -0.5f, 1.0f, 0.0f, // 1
        0.5f,  0.5f,  1.0f, 1.0f, // 2
        -0.5f, 0.5f,  0.0f, 1.0f  // 3
    };
    // index buffer
    unsigned int indices[] = {0, 1, 2, 0, 3, 2};
    // vertex array object
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;

    // vertex buffer object
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    // vertex buffer layout
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    Shader shader = Shader("res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    Texture texture("res/textures/texture.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    float r = 0.0f;
    float increment = 0.05f;
    ClearAll();
    /* Loop until the user closes the window */
    Renderer renderer;
    do {
      /* Render here */
      renderer.Clear();
      shader.Bind();
      shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
      /* Core Profile */
      va.Bind();
      /* Compat Profile
      GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
      GLCALL(glEnableVertexAttribArray(0));
      GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2,
      0));
      */
      ib.Bind();
      renderer.Draw(va, ib, shader);
      // GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();

      // change color
      if (r > 1.0f) {
        increment = -0.05f;
      } else if (r < 0.0f) {
        increment = 0.05f;
      }
      r += increment;
    } while (glfwWindowShouldClose(window) == 0 &&
             glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

    glfwTerminate();
  }
  return 0;
}
