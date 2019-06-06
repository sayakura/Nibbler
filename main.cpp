#include <iostream>
#include <string>
#include <chrono>
#include "GLDebug.hpp"
#include "Game.hpp"

#include "GLFW/glfw3.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "ResourceManager.hpp"
#include <unistd.h>


//unsigned int WINWIDTH = 800;
//unsigned int WINHEIGHT = 600;

unsigned int SQUARESIZE = 24;

unsigned int ROWS = 24;
unsigned int COLS = 32;

//first two parameters set location of lower left corner
//third and fourth set width and height of rendering window in pixels
//Note that processed coordinates in OpenGL are between -1 and 1 so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600)
/*void framebufferSizeCallback(GLFWwindow * window, int width, int height)
{
	GLCall(glViewport(0, 0, width, height));
}

void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			gamePtr->_keys[key] = true;
		else if (action == GLFW_RELEASE)
			gamePtr->_keys[key] = false;
	}
	return;
}*/

int main(int argc, char** argv)
{
	//squaresize * 2 for border
	unsigned int WINWIDTH = (SQUARESIZE * COLS) + SQUARESIZE * 2;
	unsigned int WINHEIGHT = (SQUARESIZE * ROWS) + SQUARESIZE * 2;

	Renderer *renderer;
	renderer = new Renderer(WINWIDTH, WINHEIGHT, SQUARESIZE);

	bool quit = false;
	Game game(renderer, WINWIDTH, WINHEIGHT, SQUARESIZE);


	game.init();

	std::chrono::duration<double> deltaTime;
	auto lastFrame = std::chrono::high_resolution_clock::now();

	game.setGameState(Active);

	while (!quit)
	{
		auto currentFrame = std::chrono::high_resolution_clock::now();
		//float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		game.processInput(deltaTime.count());

		game.update(deltaTime.count());

		if(game.getGameState() == Quit)
			quit = true;

		game.render();
	}

	return 0;
}
