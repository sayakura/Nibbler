NAME = test
SOURCE = AppleMaker.cpp \
		 Callbacks.cpp \
		 Camera.cpp \
		 Cube.cpp \
		 GLDebug.cpp \
		 IndexBuffer.cpp \
		 Game.cpp \
         Quad.cpp \
		 Renderer.cpp \
		 Renderer3D.cpp \
		 ResourceManager.cpp \
		 Shader.cpp \
		 Snake.cpp \
		 Texture.cpp \
		 TextRenderer.cpp \
		 VertexArray.cpp \
		 VertexBuffer.cpp \
		 glad.cpp \
		 main.cpp \
		 vendor/stb_image/stb_image.cpp \
		 vendor/imgui/*.cpp
INCLUDES = -I./\
		   -Iinclude/\
		   -I/nfs/2018/d/dpeck/.brew/Cellar/glfw/3.3/include \
		   -I/nfs/2018/d/dpeck/.brew/Cellar/freetype/2.9.1/include/freetype2 \
           -I/usr/local/Cellar/glf2/3.3/include
LIB = -L/nfs/2018/d/dpeck/.brew/Cellar/glfw/3.3/lib \
	  -L/nfs/2018/d/dpeck/.brew/Cellar/freetype/2.9.1/lib
DEPEND = -lglfw -lfreetype -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon


all: $(NAME)

$(NAME):
	clang++ -std=c++11 -stdlib=libc++ $(INCLUDES) $(LIB) $(DEPEND) $(SOURCE)

clean:
	/bin/rm -f *.o

flcean: clean
	/bin/rm $(NAME)

re: fclean all
