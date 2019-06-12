NAME = test
SOURCE = Callbacks.cpp \
		 Camera.cpp \
		 Cube.cpp \
		 GLDebug.cpp \
		 IndexBuffer.cpp \
		 Game.cpp \
		 Gameboard.cpp \
		 OpenGLDraw.cpp \
		 OpenGLHelper.cpp \
		 OpenGLInit.cpp \
		 OpenGLInput.cpp \
         Quad.cpp \
		 RandomlyPlacedObject.cpp \
		 RendererA.cpp \
		 RendererB.cpp \
		 RendererC.cpp \
		 ResourceManager.cpp \
		 Shader.cpp \
		 Snake.cpp \
		 Texture.cpp \
		 TextRenderer.cpp \
		 VertexArray.cpp \
		 VertexBuffer.cpp \
		 main.cpp \
		 vendor/stb_image/stb_image.cpp \
		 vendor/imgui/*.cpp \
		 helpers.cpp\
		 SoundEngine.cpp
		 
INCLUDES = -I./\
		   -Iinclude/freetype\
		   -Iinclude/glad\
		   -Iinclude/GLFW\
		   -Iinclude/KHR\
		   -Iinclude\

LIB = -Llib
DEPEND = -lglfw -lfreetype -lirrklang -lglad\
		 -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon

all: $(NAME)

$(NAME):
		clang++ -std=c++11 -stdlib=libc++ $(INCLUDES) $(LIB) $(DEPEND) $(SOURCE)
clean:
	/bin/rm -f *.o

flcean: clean
	/bin/rm $(NAME)

re: fclean all
