cmake_minimum_required(VERSION 3.12)

project(OpenGLProject)

# Setze den C++-Standard auf C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Füge die Pfade für die Header-Dateien hinzu
include_directories(Depencies/GLEW/include)
include_directories(Depencies/GLFW/include)
include_directories(src/vendor)
include_directories(src/test)
include_directories(src)

add_definitions(-DGLEW_STATIC)

# Füge die Quelldateien hinzu
set(SOURCES
 src/Application.cpp
 src/IndexBuffer.cpp
 src/Renderer.cpp
 src/VertexArray.cpp
 src/VertexBuffer.cpp
 src/VertexBufferLayout.cpp
 src/Shader.cpp
 src/Texture.cpp
 src/vendor/stb_image/stb_image.cpp
 src/vendor/imgui/imgui.cpp
 src/vendor/imgui/imgui_demo.cpp
 src/vendor/imgui/imgui_draw.cpp
 src/vendor/imgui/imgui_impl_glfw.cpp
 src/vendor/imgui/imgui_impl_opengl3.cpp
 src/vendor/imgui/imgui_tables.cpp
 src/vendor/imgui/imgui_widgets.cpp
 src/tests/Test.cpp
 src/tests/TestClearColor.cpp
 src/tests/TestTexture2D.cpp
 src/tests/TestBatchRendering.cpp
  )

# Füge die Bibliotheksverzeichnisse hinzu (jetzt relativ zum Projektverzeichnis)
link_directories(Depencies/GLEW/lib/Release/x64)
link_directories(Depencies/GLFW/lib-mingw-w64) 


# Erstelle das ausführbare Ziel
add_executable(application ${SOURCES})

# Füge die Bibliotheken hinzu, die zum Linken benötigt werden
target_link_libraries(application glew32s glfw3 opengl32 User32 Gdi32 Shell32)

# Füge Debugging-Flags hinzu
# target_compile_options(application PRIVATE -g)

# Kompiliere und linke die Anwendung statisch
set_target_properties(application PROPERTIES LINK_FLAGS "-static")
