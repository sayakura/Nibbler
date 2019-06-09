/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:20:49 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/07 20:14:12 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.hpp"
#include "GLDebug.hpp"
#include "ResourceManager.hpp"
#include "VertexArray.hpp"
#include "Quad.hpp"
#include "SnakeSprite.hpp"
#include <iomanip>

std::unordered_map<std::string, float(*)[12]> Renderer::_snakeSpriteMap = Renderer::initSnakeSpriteMap();


std::unordered_map<std::string, float(*)[12]> Renderer::initSnakeSpriteMap()
{
	std::unordered_map<std::string, float(*)[12]> map;
	map["rightToDown"] = &SnakeSprite::rightToDown;
	map["horizontal"] = &SnakeSprite::horizontal;
	map["leftToDown"] = &SnakeSprite::leftToDown;
	map["headUp"] = &SnakeSprite::headUp;
	map["headLeft"] = &SnakeSprite::headLeft;
	map["headRight"] = &SnakeSprite::headRight;
	map["headDown"] = &SnakeSprite::headDown;
	map["vertical"] = &SnakeSprite::vertical;
	map["rightToUp"] = &SnakeSprite::rightToUp;
	map["leftToUp"] = &SnakeSprite::leftToUp;
	map["tailDown"] = &SnakeSprite::tailDown;
	map["tailUp"] = &SnakeSprite::tailUp;
	map["tailLeft"] = &SnakeSprite::tailLeft;
	map["tailRight"] = &SnakeSprite::tailRight;
	return (map);
}

Renderer::Renderer(unsigned int width, unsigned int height, unsigned int squareSize) : 
	_clearColor(0.0f), _width(width), _height(height), _squareSize(squareSize), _borderOffset(squareSize * 2), _score(0),
	_snakeObj(NULL), _appleObj(NULL), _border(NULL), _background(NULL), _textRenderer(nullptr), _window(NULL)
{
}

//everything in this class can't be created until GLFW init functions are called
//wanted to maintain the error checking of these functions. so use an init function rather than constructor
bool Renderer::init()
{
	if (initGLFW() == -1)
		return (false);

	allocateDrawObjects();
		
	_textRenderer = new TextRenderer(_width, _height);
    _textRenderer->load("fonts/Stencil8bit-Regular.otf", _squareSize + _squareSize / 2);

	//VertexBufferLayout used to organize buffer data for shaders
	_layout.push<float>(2);
	_offsets.push_back(2);
	_layout.push<float>(2);
	_offsets.push_back(2);

	if (!initResources())
		return (false);

	buildBackground();
	buildBorder();
	buildApple();

	_ss << std::setfill('0') << std::setw(3) << _score;

	return (true);
}

void Renderer::allocateDrawObjects()
{
	_snakeObj = new ObjectDrawingInfo;
	_appleObj = new ObjectDrawingInfo;
	_border = new ObjectDrawingInfo;
	_background = new ObjectDrawingInfo;
}

bool Renderer::initResources()
{
	Shader *shader = &ResourceManager::loadShader("./shaders/basic.shader", "default");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(_width), static_cast<float>(_height), 0.0f, -1.0f, 1.0f);
    if (shader != nullptr)
    {
        shader->bind();
        shader->setUniformMat4f("u_projection", projection);
    }
	else
		return (false);
	
    shader = &ResourceManager::loadShader("./shaders/text.shader", "text");
    if (shader != nullptr)
    {
        shader->bind();
        shader->setUniformMat4f("u_projection", projection);
    }
	else
		return (false);
	
    ResourceManager::loadTexture("./textures/snake-graphics.png", GL_TRUE, GL_FALSE, "snake");
    ResourceManager::loadTexture("./textures/grass.png", GL_TRUE, GL_TRUE, "grass");
    ResourceManager::loadTexture("./textures/tree.png", GL_TRUE, GL_FALSE, "tree");

	return (true);
}

Renderer::~Renderer()
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

int Renderer::initGLFW()
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

void Renderer::drawSprite(Texture & texture, const VertexArray & va, Shader & shader, unsigned int numOfVertices, glm::vec3 color)
{
	shader.bind();
	glm::mat4 model(1.0f);

	shader.setUniformMat4f("u_model", model);
	shader.setUniform3f("u_spriteColor", color.x, color.y, color.z);

	texture.bind(0);
	shader.setUniform1i("u_Image", 0); //might be able to make this call in another function

	va.bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));
}

void Renderer::drawApple(Texture & texture, glm::vec2 pos, const VertexArray & va, Shader & shader, const unsigned int numOfVertices, glm::vec2 size, glm::vec3 color)
{
	shader.bind();
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.setUniformMat4f("u_model", model);
	shader.setUniform3f("u_spriteColor", color.x, color.y, color.z);

	texture.bind();
	shader.setUniform1i("u_Image", 0);

	va.bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));
}

void Renderer::clear() const
{
	GLCall(glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::setClearColor(glm::vec4 color)
{
	_clearColor = color;
}

void Renderer::refreshSnakeBuffer(std::vector<float> snakeVertices)
{
	_snakeObj->vertices = snakeVertices;
    if (_snakeObj->vb != nullptr)
        delete _snakeObj->vb;
    _snakeObj->vb = new VertexBuffer(&snakeVertices[0], snakeVertices.size() * sizeof(float), GL_STATIC_DRAW);
    _snakeObj->va.addBuffer(*(_snakeObj->vb), _layout);
}

void Renderer::buildBackground()
{
     float  texCoords[12] = {0.0f, 1.0f, 
                            1.0f, 0.0f, 
                            0.0f, 0.0f,
                            0.0f, 1.0f,
                            1.0f, 1.0f,
                            1.0f, 0.0f};

	//could try tiling by the texture size instead of the squaresize. doesn't make much of a difference now. but might on a bigger window
    unsigned int totalRows = _height / _squareSize;
    unsigned int totalCols = _width / _squareSize;
    unsigned int posX = 0;
    unsigned int posY = 0;

    std::vector<float> quadCoords;
    
    for (unsigned int i = 0; i < totalRows; i++)
    {
        posX = 0;
        for (unsigned int j = 0; j < totalCols; j++)
        {
            quadCoords = Quad::getPosCoords(posX, posY, _squareSize);
            Quad::buildVertex(_background->vertices, quadCoords, _offsets, texCoords);
            posX += _squareSize;
        }
        posY += _squareSize;
    }

    _background->vb = new VertexBuffer(&_background->vertices[0], _background->vertices.size() * sizeof(float), GL_STATIC_DRAW);
    _background->va.addBuffer(*_background->vb, _layout);
}

void Renderer::buildBorder()
{
    float  texCoords[12] = {0.0f, 1.0f, 
                            1.0f, 0.0f, 
                            0.0f, 0.0f,
                            0.0f, 1.0f,
                            1.0f, 1.0f,
                            1.0f, 0.0f};

	unsigned int borderSquare = _squareSize * 2;
    unsigned int totalRows = (_height - _borderOffset * 2) / borderSquare;
    unsigned int totalCols = (_width - _borderOffset * 2) / borderSquare;
    unsigned int posX = _borderOffset;
    unsigned int botY = (totalRows) * borderSquare;

    std::vector<float> quadCoords;
    
    for (unsigned int i = 0; i < totalCols; i++)
    {
        quadCoords = Quad::getPosCoords(posX, _borderOffset, borderSquare);
        Quad::buildVertex(_border->vertices, quadCoords, _offsets, texCoords);
        quadCoords = Quad::getPosCoords(posX, botY, borderSquare);
        Quad::buildVertex(_border->vertices, quadCoords, _offsets, texCoords);
        posX += borderSquare;
    }

    unsigned int rightX = (totalCols) * borderSquare;
    unsigned int posY = _borderOffset + borderSquare;

    for (unsigned int i = 1; i < totalRows; i++)
    {
        quadCoords = Quad::getPosCoords(_borderOffset, posY, borderSquare);
        Quad::buildVertex(_border->vertices, quadCoords, _offsets, texCoords);
        quadCoords = Quad::getPosCoords(rightX, posY, borderSquare);
        Quad::buildVertex(_border->vertices, quadCoords, _offsets, texCoords);
        posY += borderSquare;
    }

    _border->vb = new VertexBuffer(&_border->vertices[0], _border->vertices.size() * sizeof(float), GL_STATIC_DRAW);
    _border->va.addBuffer(*_border->vb, _layout);
}

void Renderer::updateScore()
{
    _ss.str("");
    _score++;
    _ss << std::setfill('0') << std::setw(3) << _score;	
}

void Renderer::draw()
{
	//GLFWwindow *window = glfwGetCurrentContext();

	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	drawSprite(ResourceManager::getTexture("grass"), _background->va, ResourceManager::getShader("default"), _background->vertices.size(), glm::vec3(0.376, 0.784, 0.545));
    drawSprite(ResourceManager::getTexture("tree"), _border->va, ResourceManager::getShader("default"), _border->vertices.size());
    _textRenderer->renderText("Score: " + _ss.str(), _borderOffset + 1.0f, _borderOffset / 3.0f, 1.0f);
    drawSprite(ResourceManager::getTexture("snake"), _snakeObj->va, ResourceManager::getShader("default"), _snakeObj->vertices.size());
    drawApple(ResourceManager::getTexture("snake"), glm::vec2(_appleX, _appleY), _appleObj->va, ResourceManager::getShader("default"), _appleObj->vertices.size(), glm::vec2(static_cast<float>(_squareSize), static_cast<float>(_squareSize)));

	glfwSwapBuffers(glfwGetCurrentContext());
}

void Renderer::buildApple()
{
	_appleObj->vb = new VertexBuffer(&SnakeSprite::apple[0], 4 * sizeof(float) * 6, GL_STATIC_DRAW);
    _appleObj->va.addBuffer(*_appleObj->vb, _layout);
    _appleObj->vertices.assign(SnakeSprite::apple, SnakeSprite::apple + 24);
}

void Renderer::updateApple(const float & x, const float & y)
{
	this->_appleX = x;
	this->_appleY = y;
}

void Renderer::processInput(Direction & curDirection)
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

void Renderer::buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture)
{
    std::vector<float> startingPositions;
	startingPositions = Quad::getPosCoords(x, y, _squareSize);
    Quad::buildVertex(buffer, startingPositions, _offsets, *(Renderer::_snakeSpriteMap[texture]));	
}

void Renderer::changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture)
{
	int idx = (tail) ? 0 : (Quad::_rows * Quad::_cols) * (size - 2);
	float * texCoords = *Renderer::_snakeSpriteMap[texture];
    int texCount = 0;
    unsigned int curRow = 0;
    if (idx != 0)
        curRow = idx / Quad::_cols;
    for (unsigned int i = 0; i < Quad::_rows; i++)
    {
        for (unsigned int j = 0; j < _offsets[1]; j++)
        {
            buffer[curRow * Quad::_cols + j + _offsets[0]] = texCoords[texCount];
            texCount++;
        }
        curRow++;
    }	
}

void Renderer::popSnakeTail(std::deque<float> & buffer)
{
	for (unsigned int i = 0; i < Quad::_rows; i++)
	{
		for (unsigned int j = 0; j < Quad::_cols; j++)
			buffer.pop_front();
	}	
}