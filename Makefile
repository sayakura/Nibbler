SHELL:=zsh
NAME = test
SOURCE = src/main.cpp \
		src/helpers.cpp \
		src/Snake.cpp \
		src/Game.cpp \
		src/Gameboard.cpp \
		src/RandomlyPlacedObject.cpp  \

SOURCE2 = \
		 notused/OpenGLDraw.cpp \
		 notused/OpenGLHelper.cpp \
		 notused/OpenGLInit.cpp \
		 notused/OpenGLInput.cpp \
		 notused/Camera.cpp \
		 notused/Cube.cpp \
		 notused/GLDebug.cpp \
		 notused/IndexBuffer.cpp \
         notused/Quad.cpp \
		 notused/ResourceManager.cpp \
		 notused/Shader.cpp \
		 notused/Texture.cpp \
		 notused/TextRenderer.cpp \
		 notused/VertexArray.cpp \
		 notused/VertexBuffer.cpp \
		 notused/SoundEngine.cpp \
		 notused/Callbacks.cpp \
		 notused/vendor/stb_image/stb_image.cpp \

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

pre: ascii
	@rm -rf lib
	@mkdir lib
	@echo "Unziping all the dependencies..." 
	@unzip -a lib.zip -d lib
	@print "Type \e[4m\e[7m\e[91mexport DYLD_LIBRARY_PATH=lib\e[0m to set up the env"

dylib: ascii
	@echo "Creating all the dylib..."
	@clang++ -Wall -Wextra -Werror -std=c++11 -c -stdlib=libc++ -I./ -Iinclude/freetype -Iinclude/glad -Iinclude/GLFW -Iinclude/KHR -Iinclude  $(SOURCE2)
	@clang++ -Wall -Wextra -Werror -dynamiclib -undefined suppress -flat_namespace *.o -o libopenglshits.dylib
	@print "\e[7m\e[91mlibopenglshits.dylib\e[0m created" 
	@/bin/rm -f *.o

recompile:
	@clang++ -O2 -Wall -Wextra -Werror -std=c++11 -stdlib=libc++ $(INCLUDES) $(LIB) $(DEPEND) $(SOURCE) -o Nibbler

ascii:
	@echo "\
_____________________________________________________\n\
ooo____oo__oo__oo______oo______ooo___________________\n\
oooo___oo______oooooo__oooooo___oo____ooooo__oo_ooo__\n\
oo_oo__oo__oo__oo___oo_oo___oo__oo___oo____o_ooo___o_\n\
oo__oo_oo__oo__oo___oo_oo___oo__oo___ooooooo_oo______\n\
oo___oooo__oo__oo___oo_oo___oo__oo___oo______oo______\n\
oo____ooo_oooo_oooooo__oooooo__ooooo__ooooo__oo______\n\
_____________________________________________________"
clean:
	/bin/rm -f *.o
fclean:
	/bin/rm Nibbler
	rm -rf lib 
re: fclean all
