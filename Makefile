SHELL:=zsh
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
		 SoundEngine.cpp\

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

$(NAME): pre
	@echo "Compiling all the files into executable..."
	@clang++ -O2 -Wall -Wextra -Werror -std=c++11 -stdlib=libc++ $(INCLUDES) $(LIB) $(DEPEND) $(SOURCE) -o Nibbler
	@print "\e[7m\e[91mNibbler\e[0m created"
	@echo "Enjoy the game!"

pre: dylib
	@echo "Unziping all the dependencies..." 
	@unzip -a lib.zip -d lib
	@print "Type \e[4m\e[7m\e[91mexport DYLD_LIBRARY_PATH=lib\e[0m to set up the env"

dylib:
	@echo "\
	    _   ________    __         \n\
   / | / /  _/ /_  / /_  ___  _____\n\
  /  |/ // // __ \/ __ \/ _ \/ ___/\n\
 / /|  // // /_/ / /_/ /  __/ /    \n\
/_/ |_/___/_.___/_.___/\___/_/     "
	@echo "Creating all the dylib..."
	@mkdir lib
	@clang++ -O2 -Wall -Wextra -Werror -std=c++11 -c -stdlib=libc++ -I./ -Iinclude/freetype -Iinclude/glad -Iinclude/GLFW -Iinclude/KHR -Iinclude OpenGLDraw.cpp OpenGLHelper.cpp OpenGLInit.cpp OpenGLInput.cpp
	@clang++ -Wall -Wextra -Werror -dynamiclib -undefined suppress -flat_namespace *.o -o libopenglshits.dylib
	@print "\e[7m\e[91mlibopenglshits.dylib\e[0m created" 
	@clang++ -Wall -Wextra -Werror -std=c++11 -c -stdlib=libc++ -I./ -Iinclude/freetype -Iinclude/glad -Iinclude/GLFW -Iinclude/KHR -Iinclude RendererA.cpp RendererB.cpp RendererC.cpp  
	@clang++ -dynamiclib -undefined suppress -flat_namespace RendererA.o -o renderA.dylib
	@print "\e[7m\e[91mrenderA.dylib\e[0m created" 
	@clang++ -dynamiclib -undefined suppress -flat_namespace RendererB.o -o renderB.dylib
	@print "\e[7m\e[91mrenderB.dylib\e[0m created" 
	@clang++ -dynamiclib -undefined suppress -flat_namespace RendererC.o -o renderC.dylib
	@print "\e[7m\e[91mrenderC.dylib\e[0m created" 
	@/bin/rm -f *.o
	@mv *.dylib lib

recompile:
	@clang++ -O2 -Wall -Wextra -Werror -std=c++11 -stdlib=libc++ $(INCLUDES) $(LIB) $(DEPEND) $(SOURCE) -o Nibbler

clean:
	/bin/rm -f *.o

flcean:
	/bin/rm Nibbler
	rm -rf lib 
re: fclean all
