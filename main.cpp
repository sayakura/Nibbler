#include <iostream>
#include <chrono>
#include "Game.hpp"
#include "Renderer.hpp"
#include "Renderer3D.hpp"

//unsigned int WINWIDTH = 800;
//unsigned int WINHEIGHT = 600;

unsigned int SQUARESIZE = 24;

unsigned int ROWS = 24;
unsigned int COLS = 32;

int main(int argc, char** argv)
{
	//squaresize * 2 for border
	unsigned int WINWIDTH = (SQUARESIZE * COLS) + SQUARESIZE * 2;
	unsigned int WINHEIGHT = (SQUARESIZE * ROWS) + SQUARESIZE * 2;
	std::cout << WINWIDTH << " " << WINHEIGHT << std::endl;

	IRenderer *renderer;
	renderer = new Renderer3D(WINWIDTH, WINHEIGHT, SQUARESIZE);
	renderer->init();

	bool quit = false;
	Game game(renderer, WINWIDTH, WINHEIGHT, SQUARESIZE);

	game.init();

	std::chrono::duration<float> deltaTime;
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

		try {
			game.render();
		} catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
			exit(1);
		}

	}

	return 0;
}
