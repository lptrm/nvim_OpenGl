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
// for maths :D
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
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
    // vertex positions
    /*
    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f,  -0.5f, 1.0f, 0.0f, // 1
        0.5f,  0.5f,  1.0f, 1.0f, // 2
        -0.5f, 0.5f,  0.0f, 1.0f  // 3
    };
    */
    float positions[] = {
        -250.0f, -250.0f, 0.0f, 0.0f, // 0
        250.0f,  -250.0f, 1.0f, 0.0f, // 1
        250.0f,  250.0f,  1.0f, 1.0f, // 2
        -250.0f, 250.0f,  0.0f, 1.0f  // 3
    };

    // index buffer
    unsigned int indices[] = {0, 1, 2, 0, 3, 2};
    // vertex array object
    GLCALL(glEnable(GL_BLEND));
    // takes the source alpha value and multiplies it by the source color
    // value, and then adds it to the destination color value multiplied by
    // one minus the source alpha value. (add is chosen per default)
    // TODO: practice on paper
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
    // projection matrix: maps the coordinates to a specific screen space by
    // multipliing with a matrix (orthographic projection) the function
    // parameters are: left, right, bottom, top, near, far and the resulting
    // matrix is in form of a 4x4 matrix with 2 / (right - left), ... on the
    // diagonal and 1 on the bottom right corner
    glm::mat4 proj = glm::ortho(0.0f, 768.0f, 0.0f, 1024.0f, -1.0f, 1.0f);
    // view matrix: moves the whole scene around to the right by 100
    // units which is the same as rotating the camera to the left by 100
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    // model matrix: moves the object around by 200 units to the right and 200
    // to the top

    Shader shader = Shader("res/shaders/Basic.shader");
    shader.Bind();
    // shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    Texture texture("res/textures/texture.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
    float r = 0.0f;
    float increment = 0.05f;
    ClearAll();
    /* Loop until the user closes the window */
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
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    glm::vec3 translationA(200, 200, 0);
    glm::vec3 translationB(400, 400, 0);
    do {
      /* Render here */
      renderer.Clear();
      // change color
      if (r > 1.0f) {
        increment = -0.05f;
      } else if (r < 0.0f) {
        increment = 0.05f;
      }
      r += increment;

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
        glm::mat4 u_MVP = proj * view * model;
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", u_MVP);
        renderer.Draw(va, ib, shader);
      }
      {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
        glm::mat4 u_MVP = proj * view * model;
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", u_MVP);
        renderer.Draw(va, ib, shader);
      }

      ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!"
                                     // and append into it.

      ImGui::Text("This is some useful text."); // Display some text (you can
                                                // use a format strings too)
      ImGui::SliderFloat3("logo a", &translationA.x, 0.0f, 1080.0f);
      ImGui::SliderFloat3("logo b", &translationB.x, 0.0f, 1080.0f);
      ImGui::ColorEdit3(
          "clear color",
          (float *)&clear_color); // Edit 3 floats representing a color

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / io.Framerate, io.Framerate);
      ImGui::End();

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      // GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
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
