#include <iostream>
#include <chrono>
#include "Game.hpp"
#include "RendererA.hpp"
#include "RendererB.hpp"
#include "RendererC.hpp"
#include "helpers.hpp"
#include "SoundEngine.hpp"
#include "sysconfig.hpp"
#include "Gameboard.hpp"

//unsigned int WINWIDTH = 800;
//unsigned int WINHEIGHT = 600;

unsigned int SQUARESIZE = 24;

unsigned int ROWS = 24;
unsigned int COLS = 32;

int main(int argc, char** argv)
{
	g_soundEngine = new SoundEngine();
	//squaresize * 2 for border
	unsigned int WINWIDTH = (SQUARESIZE * COLS) + SQUARESIZE * 2;
	unsigned int WINHEIGHT = (SQUARESIZE * ROWS) + SQUARESIZE * 2;
	std::cout << WINWIDTH << " " << WINHEIGHT << std::endl;



	getArgs(argc, argv);

	//this should probably be set in a better way.
	Gameboard::windowWidth = WINWIDTH;
	Gameboard::windowHeight = WINHEIGHT;
	Gameboard::squareSize = SQUARESIZE;


	IRenderer *renderer;
	renderer = new RendererA();
	Gameboard::gameMode = 1; // GAMEMODE MUST BE EQUAL TO CURRENT RENDERER OR EVERYTHING BREAKS	
	if (!renderer->initGL())
		return (1);
	renderer->init();

	bool quit = false;
	Game game(renderer, WINWIDTH, WINHEIGHT, SQUARESIZE);

	game.init();
	g_soundEngine->playLoop(SE_BGM);
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

	renderer->cleanupGL();

	return 0;
}
