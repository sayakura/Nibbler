/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer3D.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:12:33 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/06 20:00:18 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer3D.hpp"
#include "Callbacks.hpp"
#include "ResourceManager.hpp"
#include <iomanip>

Renderer3D::Renderer3D(unsigned int width, unsigned int height, unsigned int squareSize) :
    _width(width), _height(height), _squareSize(squareSize), _borderOffset(squareSize * 2), _score(0),
	_snakeObj(NULL), _appleObj(NULL), _border(NULL), _background(NULL), _textRenderer(nullptr), _window(NULL)
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

    //TODO
	/*buildBackground();
	buildBorder();
	buildApple();*/

	_ss << std::setfill('0') << std::setw(3) << _score;

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
	GLCall(glEnable(GL_CULL_FACE));
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
    //TODO need to load and set up proper shaders for 3D

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

void Renderer3D::draw()
{

}

void Renderer3D::updateApple(const float & x, const float & y)
{
	this->_appleX = x;
	this->_appleY = y;
}

void Renderer3D::refreshSnakeBuffer(std::vector<float> buffer)
{
    
}

void Renderer3D::processInput(Direction & curDirection)
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
		curDirection = None;   
}

void Renderer3D::updateScore()
{
    _ss.str("");
    _score++;
    _ss << std::setfill('0') << std::setw(3) << _score;	    
}

void Renderer3D::buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture)
{
    
}

void Renderer3D::changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture)
{

}

void Renderer3D::popSnakeTail(std::deque<float> & buffer)
{
    
}