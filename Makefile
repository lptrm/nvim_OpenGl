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
					src/vendor/stb_image/stb_image.cpp \
					src/vendor/imgui/imgui.cpp \
					src/vendor/imgui/imgui_demo.cpp \
					src/vendor/imgui/imgui_draw.cpp \
					src/vendor/imgui/imgui_impl_glfw.cpp \
					src/vendor/imgui/imgui_impl_opengl3.cpp \
					src/vendor/imgui/imgui_tables.cpp \
					src/vendor/imgui/imgui_widgets.cpp

all: application.exe

application.exe: $(SOURCE)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f application.exe
