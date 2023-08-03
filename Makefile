CXX = g++
CXXFLAGS = -std=c++17 -Isrc/vendor -IDepencies/GLEW/include -IDepencies/GLFW/include -DGLEW_STATIC -g
LDFLAGS = -LDepencies/GLEW/lib/Release/x64 -LDepencies/GLFW/lib-mingw-w64 -lglew32s -lglfw3 -lopengl32 -lUser32 -lGdi32 -lShell32 
SOURCE = src/Application.cpp \
					src/Shader.cpp \
					src/IndexBuffer.cpp \
					src/Renderer.cpp \
					src/VertexArray.cpp \
					src/VertexBuffer.cpp \
					src/VertexBufferLayout.cpp \
					src/Texture.cpp \
					src/vendor/stb_image/stb_image.cpp

all: application.exe

application.exe: $(SOURCE)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f application.exe
