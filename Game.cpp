/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:19:43 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/05 17:05:57 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "SnakeSprite.hpp"
#include "Quad.hpp"
#include <iostream>
#include <iomanip>

Game::Game(unsigned int & width, unsigned int & height, unsigned int & squareSize) :
    _state(Active), _width(width), _keys(), _height(height), _renderer(nullptr),
    _snake(nullptr), _apple(nullptr), _snakeObj(nullptr), _appleObj(nullptr), _border(nullptr), _background(nullptr),
    _text(nullptr), _curDirection(Right), _squareSize(squareSize), _score(0)
{
    for (int i = 0; i < 1024; i++)
        _keys[i] = false;
    _snakeObj = new ObjectDrawingInfo;
    _appleObj = new ObjectDrawingInfo;
    _border = new ObjectDrawingInfo;
    _background = new ObjectDrawingInfo;
    _text = new ObjectDrawingInfo;
    _snakeObj->vb = nullptr;
    _appleObj->vb = nullptr;
    _border->vb = nullptr;
    _background->vb = nullptr;
    _text->vb = nullptr;

	_borderOffset = _squareSize * 2;
}

Game::~Game()
{
    if (_snakeObj->vb != nullptr)
        delete _snakeObj->vb;
    if (_appleObj->vb != nullptr)
        delete _appleObj->vb;
    if (_border->vb != nullptr)
        delete _border->vb;
    if (_background->vb != nullptr)
        delete _background->vb;
    if (_text->vb != nullptr)
        delete _text->vb;
    if (_text != nullptr)
        delete _text;
    if (_renderer != nullptr)
        delete _renderer;
    if (_snakeObj != nullptr)
        delete _snakeObj;
    if (_appleObj != nullptr)
        delete _appleObj;
    if (_border != nullptr)
        delete _border;
    if (_background != nullptr)
        delete _background;
    if (_snake != nullptr)
        delete _snake;
    if (_apple != nullptr)
        delete _apple;
    delete _textRenderer;
}

void Game::init()
{
    _snake = new Snake(_width, _height, 6, 2, _squareSize);
	_snake->setBoundsCollision(_borderOffset);
    _apple = new AppleMaker(_width, _height, _squareSize);

    _textRenderer = new TextRenderer(_width, _height);
    _textRenderer->load("fonts/Stencil8bit-Regular.otf", _squareSize + _squareSize / 2);

	while (_snake->checkCollisionPoint(_apple->getX(), _apple->getY()))
		_apple->generateRandomPos();

	_layout.push<float>(2);
	_layout.push<float>(2);

    //inits the buffer
	refreshSnakeBuffer();

    Shader *shader = &ResourceManager::loadShader("./shaders/basic.shader", "default");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(_width), static_cast<float>(_height), 0.0f, -1.0f, 1.0f);
    if (shader != nullptr)
    {
        shader->bind();
        shader->setUniformMat4f("u_projection", projection);
    }
    shader = &ResourceManager::loadShader("./shaders/text.shader", "text");
    if (shader != nullptr)
    {
        shader->bind();
        shader->setUniformMat4f("u_projection", projection);
    }   

    ResourceManager::loadTexture("./textures/snake-graphics.png", GL_TRUE, GL_FALSE, "snake");
    ResourceManager::loadTexture("./textures/grass.png", GL_TRUE, GL_TRUE, "grass");
    ResourceManager::loadTexture("./textures/tree.png", GL_TRUE, GL_FALSE, "tree");
    _renderer = new Renderer();
   
    buildBackground();
    buildBorder();

    _appleObj->vb = new VertexBuffer(&SnakeSprite::apple[0], 4 * sizeof(float) * 6, GL_STATIC_DRAW);
    _appleObj->va.addBuffer(*_appleObj->vb, _layout);
    _appleObj->vertices.assign(SnakeSprite::apple, SnakeSprite::apple + 24);

    _ss << std::setfill('0') << std::setw(3) << _score;
}

void Game::buildBackground()
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
            Quad::buildVertex(_background->vertices, quadCoords, texCoords);
            posX += _squareSize;
        }
        posY += _squareSize;
    }

/*    float background[] = {
        0.0f, 600.0f, 0.0f, 1.0f, 
         800.0f, 0.0f, 1.0f, 0.0f, 
         0.0f, 0.0f, 0.0f, 0.0f,
         0.0f, 600.0f, 0.0f, 1.0f,
         800.0f, 600.0f, 1.0f, 1.0f,
         800.0f, 0.0f, 1.0f, 0.0f
    };

    _background->vertices.assign(background, background + 24);*/ 

    _background->vb = new VertexBuffer(&_background->vertices[0], _background->vertices.size() * sizeof(float), GL_STATIC_DRAW);
    _background->va.addBuffer(*_background->vb, _layout);
}

void Game::buildBorder()
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
        Quad::buildVertex(_border->vertices, quadCoords, texCoords);
        quadCoords = Quad::getPosCoords(posX, botY, borderSquare);
        Quad::buildVertex(_border->vertices, quadCoords, texCoords);
        posX += borderSquare;
    }

    unsigned int rightX = (totalCols) * borderSquare;
    unsigned int posY = _borderOffset + borderSquare;

    for (unsigned int i = 1; i < totalRows; i++)
    {
        quadCoords = Quad::getPosCoords(_borderOffset, posY, borderSquare);
        Quad::buildVertex(_border->vertices, quadCoords, texCoords);
        quadCoords = Quad::getPosCoords(rightX, posY, borderSquare);
        Quad::buildVertex(_border->vertices, quadCoords, texCoords);
        posY += borderSquare;
    }

    _border->vb = new VertexBuffer(&_border->vertices[0], _border->vertices.size() * sizeof(float), GL_STATIC_DRAW);
    _border->va.addBuffer(*_border->vb, _layout);
}

void Game::update(float dt)
{
    const float animationSpeed = 12.0f;
    float animationUpdateTime = 1.0f / animationSpeed;
    static float timeSinceLastFrameSwap = 0.0f;
    timeSinceLastFrameSwap += dt;

    if (timeSinceLastFrameSwap > animationUpdateTime)
    {
        if (_snake != nullptr)
        {
            if (!_snake->moveSnake(_curDirection))
                setGameState(Quit);
            //std::cout << "x: " << _snake->getHeadX() << " y: " << _snake->getHeadY() << std::endl;
            if ((int)_snake->getHeadX() == (int)_apple->getX() && (int)_snake->getHeadY() == (int)_apple->getY())
            {
				while (_snake->checkCollisionPoint(_apple->getX(), _apple->getY()))
                	_apple->generateRandomPos();
                _snake->grow();
                this->updateScore();
            }
        }
                    
        refreshSnakeBuffer();
        timeSinceLastFrameSwap = 0.0f;
    }
}

void Game::processInput(float dt)
{
    if (_keys[GLFW_KEY_UP] && _curDirection != Down)
        _curDirection = Up;
    else if (_keys[GLFW_KEY_RIGHT] && _curDirection != Left)
        _curDirection = Right;
    else if (_keys[GLFW_KEY_LEFT] && _curDirection != Right)
        _curDirection = Left;
    else if (_keys[GLFW_KEY_DOWN] && _curDirection != Up)
        _curDirection = Down;
}

void Game::render()
{
    if (_renderer != nullptr)
    {
        
        _renderer->drawSprite(ResourceManager::getTexture("grass"), _background->va, ResourceManager::getShader("default"), _background->vertices.size(), glm::vec3(0.376, 0.784, 0.545));
        _renderer->drawSprite(ResourceManager::getTexture("tree"), _border->va, ResourceManager::getShader("default"), _border->vertices.size());
        _textRenderer->renderText("Score: " + _ss.str(), _borderOffset + 1.0f, _borderOffset / 3.0f, 1.0f);
        _renderer->drawSprite(ResourceManager::getTexture("snake"), _snakeObj->va, ResourceManager::getShader("default"), _snakeObj->vertices.size());
        _renderer->drawApple(ResourceManager::getTexture("snake"), glm::vec2(_apple->getX(), _apple->getY()), _appleObj->va, ResourceManager::getShader("default"), _appleObj->vertices.size(), glm::vec2(static_cast<float>(_squareSize), static_cast<float>(_squareSize)));
    }
}

void Game::refreshSnakeBuffer()
{
    _snakeObj->vertices = _snake->getBufferAsVector();
    if (_snakeObj->vb != nullptr)
        delete _snakeObj->vb;
    _snakeObj->vb = new VertexBuffer(&_snakeObj->vertices[0], _snakeObj->vertices.size() * sizeof(float), GL_STATIC_DRAW);
    _snakeObj->va.addBuffer(*(_snakeObj->vb), _layout);
}

unsigned int Game::getWidth() const { return (_width); }

unsigned int Game::getHeight() const { return (_height); }

GameState Game::getGameState() const { return (_state); }

void Game::setGameState(GameState state)
{
    _state = state;
}

void Game::updateScore()
{
    _ss.str("");
    _score++;
    _ss << std::setfill('0') << std::setw(3) << _score;
}
