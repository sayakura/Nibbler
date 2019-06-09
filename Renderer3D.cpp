/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer3D.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:12:33 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/08 22:29:24 by qpeng            ###   ########.fr       */
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
	_camera(Camera(glm::vec3(0.0f, 0.0f, 2.0f))), _snakeSize(0)
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

	_snakeObj->vertices = Cube::getPosCoords(0.0f, 0.0f, 0);
	_snakeObj->vb = new VertexBuffer(&_snakeObj->vertices[0], _snakeObj->vertices.size() * sizeof(float), GL_DYNAMIC_DRAW);
    _snakeObj->va.addBuffer(*(_snakeObj->vb), _layout);

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
	GLCall(glEnable(GL_DEPTH_TEST));
	//GLCall(glEnable(GL_CULL_FACE));
	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

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

	//glm::mat4 proj = glm::ortho((float)-_width, static_cast<float>(_width), static_cast<float>(_height), (float)-_height, -1000.0f, 1000.0f);
	//proj = glm::rotate(proj, glm::radians(35.264f), glm::vec3(1.0f, 0.0f, 0.0f));
	//proj = glm::rotate(proj, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	/*float fov_y = 45.f;
	float z = 0.5 / glm::tan(glm::radians(fov_y / 2.0f));
	glm::mat4 view = glm::lookAt(
		glm::vec3(0.5f, 0.5f, z),
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));*/
	glm::mat4 view = _camera.getViewMatrix();
	view = glm::rotate(view, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//view = glm::rotate(view, glm::radians(-15.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	//view = glm::rotate(view, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	//view = glm::rotate(view, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//view = glm::rotate(view, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//view = glm::rotate(view, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//view = glm::rotate(view, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
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
        shader->setUniformMat4f("u_projection", proj);
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

void Renderer3D::draw()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	drawCube(_snakeObj->va, ResourceManager::getShader("threedimension"), _snakeObj->vertices.size(), glm::vec3(0.0f, 1.0f, 0.0f));

	glfwSwapBuffers(glfwGetCurrentContext());
}

void Renderer3D::drawCube(const VertexArray & va, Shader & shader, unsigned int numOfVertices, glm::vec3 color)
{
	shader.bind();
	glm::mat4 model;


	shader.setUniform3f("u_cubeColor", color.x, color.y, color.z);

	va.bind();

	for (int i = 0, j = 0; i < _snakeSize; i++, j += 3)
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
	}
}

void Renderer3D::updateApple(const float & x, const float & y)
{
	this->_appleX = x;
	this->_appleY = y;
}

void Renderer3D::refreshSnakeBuffer(std::vector<float> snakeVertices)
{
	/*_snakeObj->vertices = snakeVertices;
    if (_snakeObj->vb != nullptr)
        delete _snakeObj->vb;
    _snakeObj->vb = new VertexBuffer(&snakeVertices[0], snakeVertices.size() * sizeof(float), GL_STATIC_DRAW);
    _snakeObj->va.addBuffer(*(_snakeObj->vb), _layout);*/
	return;    
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
    /*std::vector<float> startingPositions;
	startingPositions = Cube::getPosCoords(x, y, _squareSize);
    Cube::buildVertex(buffer, startingPositions, _offsets);*/
	y = _height - y;

	//glm::vec3 pos = glm::unProject(glm::vec3(x, y, 0.0f), glm::mat4(1.0f), _proj, glm::vec4(0, 0, _width, _height));

	//float prevX = x;
	//float prevY = y;

	//x = (prevX - prevY) * glm::cos(glm::radians(30.0f));
	//y = 0.0f + (prevX + prevY) * glm::sin(glm::radians(30.0f));

	x = 2.0f * (x) / _width - 1.0f;
    y = 2.0f * (y) / _height - 1.0f;

	_snakeCoords.push_back(x);
	_snakeCoords.push_back(y);
	_snakeCoords.push_back(0.0f);
	_snakeSize++;
}

void Renderer3D::changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture)
{
	return;
}

void Renderer3D::popSnakeTail(std::deque<float> & buffer)
{
	/*for (unsigned int i = 0; i < Cube::_rows; i++)
	{
		for (unsigned int j = 0; j < Cube::_cols; j++)
			buffer.pop_front();
	}*/
	for (unsigned int i = 0; i < 3; i++)
		_snakeCoords.pop_front();
	_snakeSize--;   
}
