/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer3D.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:12:33 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/09 22:06:21 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer3D.hpp"
#include "Callbacks.hpp"
#include "ResourceManager.hpp"
#include "Cube.hpp"
#include <iomanip>

Renderer3D::Renderer3D(unsigned int width, unsigned int height, unsigned int squareSize) :
    _width(width), _height(height), _squareSize(squareSize), _borderOffset(squareSize * 2), _score(0),
	_snakeObj(NULL), _appleObj(NULL), _border(NULL), _background(NULL), _textRenderer(nullptr), _window(NULL),
	_camera(Camera(glm::vec3(0.0f, 0.0f, 2.5f))), _snakeSize(0), _pause(false), _curMenuChoice(0)
{
}

bool Renderer3D::init()
{
    if (initGLFW() == -1)
        return (false);

	allocateDrawObjects();
		
	_textRenderer = new TextRenderer(_width, _height);
    _textRenderer->load("fonts/Stencil8bit-Regular.otf", _squareSize + _squareSize / 2);

    //maybe add more if we want color coordinates or tex coordinates
	_layout.push<float>(3);
	_offsets.push_back(3);

	if (!initResources())
		return (false);

	//draw each cube of snake version WORKS
	/*_snakeObj->vertices = Cube::getPosCoords(0.0f, 0.0f, 0);
	_snakeObj->vb = new VertexBuffer(&_snakeObj->vertices[0], _snakeObj->vertices.size() * sizeof(float), GL_DYNAMIC_DRAW);
    _snakeObj->va.addBuffer(*(_snakeObj->vb), _layout);*/

    //TODO
	buildBackground();
	buildBorder();
	buildApple();

	_ss << std::setfill('0') << std::setw(3) << _score;

	_pauseStr = "-> Continue <-\t   Quit";

    return (true);
}

int Renderer3D::initGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow * _window = glfwCreateWindow(_width, _height, "Snake", NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, Callback::framebufferSizeCallback);
	glfwSwapInterval(1); //synchronize with vsync
	glfwSetKeyCallback(_window, Callback::keyCallback);

	//loads the address of OpenGL function pointers which are OS-specific
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return (-1);
	}

	//GLCall(glViewport(0, 0, WINWIDTH, WINHEIGHT));
	GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glEnable(GL_CULL_FACE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	return (0);
}

void Renderer3D::allocateDrawObjects()
{
    _snakeObj = new ObjectDrawingInfo;
	_appleObj = new ObjectDrawingInfo;
	_border = new ObjectDrawingInfo;
	_background = new ObjectDrawingInfo;   
}

bool Renderer3D::initResources()
{
	Shader *shader = &ResourceManager::loadShader("./shaders/threedimension.shader", "threedimension");

	glm::mat4 view = _camera.getViewMatrix();
	view = glm::rotate(view, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)(_width)/(float)(_height), 0.1f, 100.0f);
	_proj = proj;
    if (shader != nullptr)
    {
        shader->bind();
		shader->setUniformMat4f("u_inverse", glm::inverse(proj * view));
        shader->setUniformMat4f("u_projection", proj);
		shader->setUniformMat4f("u_view", view);
    }
	else
		return (false);
	
    shader = &ResourceManager::loadShader("./shaders/text.shader", "text");
    if (shader != nullptr)
    {
        shader->bind();
        shader->setUniformMat4f("u_projection", glm::ortho(0.0f, static_cast<float>(_width), static_cast<float>(_height), 0.0f, -1.0f, 1.0f));
    }
	else
		return (false);	

	return (true);    
}

Renderer3D::~Renderer3D()
{
	ResourceManager::clear();

	if (_snakeObj != nullptr)
		delete _snakeObj;
	if (_appleObj != nullptr)
		delete _appleObj;
	if (_border != nullptr)
		delete _border;
	if (_background != nullptr)
		delete _background;
	if (_textRenderer != nullptr)
		delete _textRenderer;

	glfwDestroyWindow(glfwGetCurrentContext());
	glfwTerminate();
}

void Renderer3D::buildBackground()
{
    unsigned int totalRows = _height / _squareSize;
    unsigned int totalCols = _width / _squareSize;
    unsigned int posX = 0;
    unsigned int posY = 0;

    std::vector<float> cubeCoords;
    
    for (unsigned int i = 0; i < totalRows; i++)
    {
        posX = 0;
        for (unsigned int j = 0; j < totalCols; j++)
        {
            cubeCoords = Cube::getCubeAtPos(posX, posY, _squareSize, _width, _height);
            Cube::buildVertex(_background->vertices, cubeCoords, _offsets);
            posX += _squareSize;
        }
        posY += _squareSize;
    }

    _background->vb = new VertexBuffer(&_background->vertices[0], _background->vertices.size() * sizeof(float), GL_STATIC_DRAW);
    _background->va.addBuffer(*_background->vb, _layout);	
}

void Renderer3D::buildBorder()
{
	unsigned int borderSquare = _squareSize;
    unsigned int totalRows = (_height - _borderOffset * 2) / borderSquare;
    unsigned int totalCols = (_width - _borderOffset * 2) / borderSquare;
    unsigned int posX = _borderOffset;
    unsigned int botY = (totalRows) * borderSquare + borderSquare;

    std::vector<float> cubeCoords;
    
    for (unsigned int i = 0; i < totalCols; i++)
    {
        cubeCoords = Cube::getCubeAtPos(posX, _borderOffset, borderSquare, _width, _height);
        Cube::buildVertex(_border->vertices, cubeCoords, _offsets);
        cubeCoords = Cube::getCubeAtPos(posX, botY, borderSquare, _width, _height);
        Cube::buildVertex(_border->vertices, cubeCoords, _offsets);
        posX += borderSquare;
    }

    unsigned int rightX = (totalCols) * borderSquare + borderSquare;
    unsigned int posY = _borderOffset + borderSquare;

    for (unsigned int i = 1; i < totalRows; i++)
    {
        cubeCoords = Cube::getCubeAtPos(_borderOffset, posY, borderSquare, _width, _height);
        Cube::buildVertex(_border->vertices, cubeCoords, _offsets);
        cubeCoords = Cube::getCubeAtPos(rightX, posY, borderSquare, _width, _height);
        Cube::buildVertex(_border->vertices, cubeCoords, _offsets);
        posY += borderSquare;
    }

    _border->vb = new VertexBuffer(&_border->vertices[0], _border->vertices.size() * sizeof(float), GL_STATIC_DRAW);
    _border->va.addBuffer(*_border->vb, _layout);	
}

void Renderer3D::buildApple()
{
	std::vector<float> appleCoords = Cube::getGenericCubeCoords();
	_appleObj->vb = new VertexBuffer(&appleCoords[0], appleCoords.size() * sizeof(float), GL_STATIC_DRAW);
    _appleObj->va.addBuffer(*_appleObj->vb, _layout);
    _appleObj->vertices = appleCoords;
}

void Renderer3D::draw()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	float alpha = 1.0f;

	if (_pause)
		alpha = 0.3;

	//if (!_pause)
	//{
	drawBackground(_background->va, ResourceManager::getShader("threedimension"), _background->vertices.size(), glm::vec4(0.0f, 0.0f, 1.0f, 1.0 * alpha));
	drawBorder(_border->va, ResourceManager::getShader("threedimension"), _border->vertices.size(), glm::vec4(1.0f, 0.0f, 1.0f, 0.4f * alpha));
	_textRenderer->renderText("Score: " + _ss.str(), _borderOffset + 1.0f, _borderOffset / 3.0f, 1.0f);
	drawApple(glm::vec2(_appleX, _appleY), _appleObj->va, ResourceManager::getShader("threedimension"), _appleObj->vertices.size(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f * alpha));	
	drawCube(_snakeObj->va, ResourceManager::getShader("threedimension"), _snakeObj->vertices.size(), glm::vec4(0.0f, 1.0f, 0.0f, 1.0 * alpha));
	//}
	if (_pause)
	{
		_textRenderer->renderText("Pause", _width / 2.3f, _height / 3.0f, 1.0f);
		_textRenderer->renderText(_pauseStr, _width / 3.7f, _height / 2.3f, 1.0f);
	}


	glfwSwapBuffers(glfwGetCurrentContext());
}

void Renderer3D::drawCube(const VertexArray & va, Shader & shader, unsigned int numOfVertices, glm::vec4 color)
{
	shader.bind();
	glm::mat4 model;


	shader.setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);

	va.bind();

	/*for (int i = 0, j = 0; i < _snakeSize; i++, j += 3)
	{
		model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.5f));
		float xScale = 2.0f / (_width / _squareSize);
		float yScale = 2.0f / (_height / _squareSize);

		model = glm::translate(model, glm::vec3(_snakeCoords[j], _snakeCoords[j + 1], _snakeCoords[j + 2]));
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(xScale, yScale, 0.1f));

		shader.setUniformMat4f("u_model", model);
		if (i == _snakeSize - 1)
			shader.setUniform3f("u_cubeColor", 0.0f, 0.0f, 1.0f);
		else
			shader.setUniform3f("u_cubeColor", color.x, color.y, color.z);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));	
	}*/
	model = glm::mat4(1.0f);
	shader.setUniformMat4f("u_model", model);
	GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));
}

void Renderer3D::drawBackground(const VertexArray & va, Shader & shader, unsigned int numOfVertices, glm::vec4 color)
{
	shader.bind();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));
	shader.setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);
	shader.setUniformMat4f("u_model", model);
	va.bind();
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void Renderer3D::drawBorder(const VertexArray & va, Shader & shader, unsigned int numOfVertices, glm::vec4 color)
{
	shader.bind();
	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.2f));

	shader.setUniformMat4f("u_model", model);
	shader.setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);

	va.bind();
	//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));
	//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));	
}

void Renderer3D::drawApple(glm::vec2 pos, const VertexArray & va, Shader & shader, const unsigned int numOfVertices, glm::vec4 color)
{
	float xScale = 2.0f / (_width / _squareSize);
	float yScale = 2.0f / (_height / _squareSize);

	shader.bind();
	glm::mat4 model(1.0f);
	//model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));

	//model = glm::translate(model, glm::vec3(0.5f * xScale, 0.5f * yScale, 0.1f));
	//model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(50.0f), glm::vec3(0.5f, 0.0f, 1.0f));
	//model = glm::translate(model, glm::vec3(-pos, 0.0f));

	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.4f));

	shader.setUniformMat4f("u_model", model);
	shader.setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);

	va.bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));	
}

void Renderer3D::updateApple(const float & x, const float & y)
{
    float inverseY = _height - y;
	this->_appleX = 2.0f * (x) / _width - 1.0f;
    this->_appleY = 2.0f * (inverseY) / _height - 1.0f;

	std::vector<float> cubeCoords = Cube::getCubeAtPos(x, y, _squareSize, _width, _height);
	std::vector<float> cubeVertices;
    Cube::buildVertex(cubeVertices, cubeCoords, _offsets);
	_appleObj->vb->updateBufferArray(&cubeVertices[0], cubeVertices.size() * sizeof(float));
	_appleObj->vertices = cubeVertices;
}

void Renderer3D::refreshSnakeBuffer(std::vector<float> snakeVertices)
{
	_snakeObj->vertices = snakeVertices;
    if (_snakeObj->vb != nullptr)
        delete _snakeObj->vb;
    _snakeObj->vb = new VertexBuffer(&snakeVertices[0], snakeVertices.size() * sizeof(float), GL_DYNAMIC_DRAW);
	_snakeObj->va.addBuffer(*(_snakeObj->vb), _layout);
	return;    
}

void Renderer3D::processInput(Direction & curDirection)
{
	if (_pause == false)
	{	
		glfwPollEvents();

		if (Callback::_keys[GLFW_KEY_UP] && curDirection != Down)
        	curDirection = Up;
		else if (Callback::_keys[GLFW_KEY_RIGHT] && curDirection != Left)
			curDirection = Right;
		else if (Callback::_keys[GLFW_KEY_LEFT] && curDirection != Right)
			curDirection = Left;
		else if (Callback::_keys[GLFW_KEY_DOWN] && curDirection != Up)
			curDirection = Down;

		if (Callback::_keys[GLFW_KEY_ESCAPE])
		{
			_pause = true;
			curDirection = Pause;
		}
	}
	else
	{
		glfwWaitEvents();

		if (Callback::_keys[GLFW_KEY_LEFT])
		{
			_curMenuChoice = 0;
			moveCursor(Left);
		}
		if (Callback::_keys[GLFW_KEY_RIGHT])
		{
			_curMenuChoice = 1;
			moveCursor(Right);
		}
		if (Callback::_keys[GLFW_KEY_ENTER] && _curMenuChoice == 0)
		{
			_pause = false;
			curDirection = Pause;
		}
		if (Callback::_keys[GLFW_KEY_ENTER] && _curMenuChoice == 1)
			curDirection = Exit;
	}
	
}

void Renderer3D::updateScore()
{
    _ss.str("");
    _score++;
    _ss << std::setfill('0') << std::setw(3) << _score;	    
}

void Renderer3D::buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture)
{
    std::vector<float> startingPositions;
	startingPositions = Cube::getCubeAtPos(x, y, _squareSize, _width, _height);
    Cube::buildVertex(buffer, startingPositions, _offsets);

	//draw each cube version WORKS
	/*y = _height - y;

	x = 2.0f * (x) / _width - 1.0f;
    y = 2.0f * (y) / _height - 1.0f;

	_snakeCoords.push_back(x);
	_snakeCoords.push_back(y);
	_snakeCoords.push_back(0.0f);
	_snakeSize++;*/
}

void Renderer3D::changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture)
{
	return;
}

void Renderer3D::popSnakeTail(std::deque<float> & buffer)
{
	for (unsigned int i = 0; i < Cube::_rows; i++)
	{
		for (unsigned int j = 0; j < Cube::_cols; j++)
			buffer.pop_front();
	}
	
	//draw each cube version WORKS
	/*for (unsigned int i = 0; i < 3; i++)
		_snakeCoords.pop_front();
	_snakeSize--;*/   
}

void Renderer3D::moveCursor(Direction direction)
{
	if (direction == Left)
		_pauseStr = "-> Continue <-\t   Quit";
	if (direction == Right)
		_pauseStr = "   Continue   \t-> Quit <-";
}

void Renderer3D::setPause(bool pause)
{
	this->_pause = pause;
}
