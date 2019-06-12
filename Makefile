NAME = test
SOURCE = Callbacks.cpp \
		 Camera.cpp \
		 Cube.cpp \
		 GLDebug.cpp \
		 IndexBuffer.cpp \
		 Game.cpp \
		 Gameboard.cpp \
         Quad.cpp \
		 RandomlyPlacedObject.cpp \
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

		#  OpenGLDraw.cpp \
		#  OpenGLHelper.cpp \
		#  OpenGLInit.cpp \
		#  OpenGLInput.cpp \
		RendererA.cpp \
		 RendererB.cpp \
		 RendererC.cpp \
		 
INCLUDES = -I./\
		   -Iinclude/freetype\
		   -Iinclude/glad\
		   -Iinclude/GLFW\
		   -Iinclude/KHR\
		   -Iinclude\

LIB = -Llib
DEPEND = -lglfw -lfreetype -lirrklang -lglad -lopenglshits\
		 -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon

all: $(NAME)

$(NAME):
		clang++ -std=c++11 -stdlib=libc++ $(INCLUDES) $(LIB) $(DEPEND) $(SOURCE)

dylib:
	clang++ -std=c++11 -c -stdlib=libc++ -I./ -Iinclude/freetype -Iinclude/glad -Iinclude/GLFW -Iinclude/KHR -Iinclude RendererA.cpp
	clang++ -std=c++11 -c -stdlib=libc++ -I./ -Iinclude/freetype -Iinclude/glad -Iinclude/GLFW -Iinclude/KHR -Iinclude RendererB.cpp
	clang++ -std=c++11 -c -stdlib=libc++ -I./ -Iinclude/freetype -Iinclude/glad -Iinclude/GLFW -Iinclude/KHR -Iinclude RendererC.cpp
	clang++ -dynamiclib -undefined suppress -flat_namespace RendererA.o -o renderA.dylib
	clang++ -dynamiclib -undefined suppress -flat_namespace RendererB.o -o renderB.dylib
	clang++ -dynamiclib -undefined suppress -flat_namespace RendererC.o -o renderC.dylib
clean:
	/bin/rm -f *.o

flcean: clean
	/bin/rm $(NAME)

re: fclean all
