#include <iostream>
#include <string>
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

Game *gamePtr;

//first two parameters set location of lower left corner
//third and fourth set width and height of rendering window in pixels
//Note that processed coordinates in OpenGL are between -1 and 1 so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600)
void framebufferSizeCallback(GLFWwindow * window, int width, int height)
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
}

int main(int argc, char** argv)
{
	//squaresize * 2 for border
	unsigned int WINWIDTH = (SQUARESIZE * COLS) + SQUARESIZE * 2;
	unsigned int WINHEIGHT = (SQUARESIZE * ROWS) + SQUARESIZE * 2;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow * window = glfwCreateWindow(WINWIDTH, WINHEIGHT, "Snake", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // handles window resizes
	glfwSwapInterval(1); //synchronize with vsync
	glfwSetKeyCallback(window, keyCallback);

	//loads the address of OpenGL function pointers which are OS-specific
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return (-1);
	}

	//GLCall(glViewport(0, 0, WINWIDTH, WINHEIGHT));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

	Game game(WINWIDTH, WINHEIGHT, SQUARESIZE);

	game.init();

	gamePtr = &game;

	/*glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(300.0f, 200.0f, 0.0f));
	model = glm::scale(model, glm::vec3(300.0f, 300.0f, 0.0f));

	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);



		VertexArray va;
		VertexBuffer vb(Shape::quad, Shape::quadVerticesSize);
		IndexBuffer	ib(Shape::quadIndices, Shape::quadIndicesCount);
		VertexBufferLayout layout;

		layout.push<float>(4);
		va.addBuffer(vb, layout);

		ShaderProgramSource source = ResourceManager::parseShader("shaders/basic.shader");
		Shader shader(source);
		shader.bind();

		glm::mat4 mvp = projection * model;
		shader.setUniform3f("u_spriteColor", 1.0f, 1.0f, 1.0f);
		shader.setUniformMat4f("u_MVP", mvp);

		Renderer renderer;*/

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	game.setGameState(Active);

	while (!glfwWindowShouldClose(window))
	{


		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		game.processInput(deltaTime);

		game.update(deltaTime);

		if(game.getGameState() == Quit)
			glfwSetWindowShouldClose(window, GL_TRUE);

		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		game.render();
		glfwSwapBuffers(window);
	}

	ResourceManager::clear();
	glfwTerminate();
	return 0;
}
