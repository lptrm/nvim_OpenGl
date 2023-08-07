// for opengl function calls
#include "tests/TestTexture.h"
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
// for maths :D
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture.h"
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
  window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
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
    GLCALL(glEnable(GL_BLEND));
    // takes the source alpha value and multiplies it by the source color
    // value, and then adds it to the destination color value multiplied by
    // one minus the source alpha value. (add is chosen per default)
    // TODO: practice on paper
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    Renderer renderer;
    const char *glsl_version = "#version 330";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    test::Test *currentTest = nullptr;
    test::TestMenu *menu = new test::TestMenu(currentTest);
    currentTest = menu;
    menu->RegisterTest<test::TestClearColor>("Clear Color");
    menu->RegisterTest<test::TestTexture>("Texture Test");

    do {
      renderer.Clear();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      if (currentTest) {
        currentTest->OnUpdate(0.0f);
        currentTest->OnRender();
        ImGui::Begin("Test");
        if (currentTest != menu && ImGui::Button("<-")) {
          delete currentTest;
          currentTest = menu;
        }
        currentTest->OnImGuiRender();
        ImGui::End();
      }
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(window);
      glfwPollEvents();

    } while (glfwWindowShouldClose(window) == 0 &&
             glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
  }
  return 0;
}
