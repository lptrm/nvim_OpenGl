CXX = g++
CXXFLAGS = -std=c++17 -IDepencies/GLEW/include -IDepencies/GLFW/include -DGLEW_STATIC -g
LDFLAGS = -LDepencies/GLEW/lib/Release/x64 -LDepencies/GLFW/lib-mingw-w64 -lglew32s -lglfw3 -lopengl32 -lUser32 -lGdi32 -lShell32 

all: application.exe

application.exe: src/Application.cpp src/Shader.cpp src/IndexBuffer.cpp src/Renderer.cpp src/VertexArray.cpp src/VertexBuffer.cpp src/VertexBufferLayout.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f application.exe
