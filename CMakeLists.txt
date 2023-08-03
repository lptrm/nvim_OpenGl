cmake_minimum_required(VERSION 3.12)

project(OpenGLProject)

# Setze den C++-Standard auf C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Füge die Pfade für die Header-Dateien hinzu
include_directories(Depencies/GLEW/include)
include_directories(Depencies/GLFW/include)

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
  )

# Füge die Bibliotheksverzeichnisse hinzu (jetzt relativ zum Projektverzeichnis)
link_directories(Depencies/GLEW/lib/Release/x64)
link_directories(Depencies/GLFW/lib-mingw-w64) 


# Erstelle das ausführbare Ziel
add_executable(application ${SOURCES})

# Füge die Bibliotheken hinzu, die zum Linken benötigt werden
target_link_libraries(application glew32s glfw3 opengl32 User32 Gdi32 Shell32)

# Kompiliere und linke die Anwendung statisch
set_target_properties(application PROPERTIES LINK_FLAGS "-static")