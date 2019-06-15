/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:19:43 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/14 19:17:07 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "SnakeSprite.hpp"
#include "sysconfig.hpp"
#include "Quad.hpp"
#include <iostream>
#include <iomanip>
#include "Gameboard.hpp"

#define NUM_OF_OBSTACLES 4

SoundEngine *g_soundEngine;

Game::Game(IRenderer *renderer) :
    _state(Active), _renderer(renderer), _snake(nullptr), _apple(nullptr), 
    _score(0), _borderOffset(Gameboard::squareSize * 2), _rendererChoice(Gameboard::gameMode), _curDirection(Right)
{
}

Game::~Game()
{
    if (_snake != nullptr)
        delete _snake;
    if (_apple != nullptr)
        delete _apple;

    for (unsigned int i = 0; i < _obstacles.size(); i++)
        delete _obstacles[i];
}

void Game::init()
{
    _snake = new Snake(_renderer);
	_snake->setBoundsCollision(_borderOffset);
    _apple = new RandomlyPlacedObject();

	while (_snake->checkCollisionPoint(_apple->getX(), _apple->getY()))
		_apple->generateRandomPos();

    setupObstacles();    

    _renderer->updateApple(_apple->getX(), _apple->getY());

    //inits the buffer
	_renderer->refreshSnakeBuffer(_snake->getBufferAsVector());
}

void Game::restart()
{
    if (_snake != nullptr)
        delete _snake;
    if (_apple != nullptr)
        delete _apple;

    _snake = new Snake(_renderer);
	_snake->setBoundsCollision(_borderOffset);
    _apple = new RandomlyPlacedObject();

	while (_snake->checkCollisionPoint(_apple->getX(), _apple->getY()))
		_apple->generateRandomPos();
    
    _state = Active;
    _renderer->init();
    _renderer->setLost(false);
    _renderer->updateApple(_apple->getX(), _apple->getY());
	_renderer->refreshSnakeBuffer(_snake->getBufferAsVector());
    _score = 0;
    _curDirection = Right;

    std::vector<RandomlyPlacedObject *>::reverse_iterator rit;
    for (rit = _obstacles.rbegin(); rit != _obstacles.rend(); rit++)
    {
        delete *rit;
        _obstacles.pop_back();
    }

    setupObstacles();
    buildObstacles();
}

void Game::setupObstacles()
{
    //should change from macro to a variable that's found through the window size.
    for (unsigned int i = 0; i < NUM_OF_OBSTACLES; i++)
    {
        _obstacles.push_back(new RandomlyPlacedObject());
        while (_snake->checkCollisionPoint(_obstacles[i]->getX(), _obstacles[i]->getY())
            || (_obstacles[i]->getX() == _apple->getX() && _obstacles[i]->getY() == _apple->getY()))
            _obstacles[i]->generateRandomPos();
        _snake->setCollisionPoint(_obstacles[i]->getX(), _obstacles[i]->getY());
    }
}


void Game::update(float dt)
{
    const float animationSpeed = 15.0f;
    float animationUpdateTime = 1.0f / animationSpeed;
    static float timeSinceLastFrameSwap = 0.0f;
    timeSinceLastFrameSwap += dt;

    if (_renderer->obstaclesHaveBeenBuilt() == false)
        buildObstacles();

    if (timeSinceLastFrameSwap > animationUpdateTime && _state == Active)
    {
        if (_snake != nullptr)
        {

            if (!_snake->moveSnake(_curDirection))
            {
                setGameState(Lost);
                _renderer->setLost(true);
            }
            //std::cout << "x: " << _snake->getHeadX() << " y: " << _snake->getHeadY() << std::endl;
            if ((int)_snake->getHeadX() == (int)_apple->getX() && (int)_snake->getHeadY() == (int)_apple->getY())
            {
				while (_snake->checkCollisionPoint(_apple->getX(), _apple->getY()))
                	_apple->generateRandomPos();
                _renderer->updateApple(_apple->getX(), _apple->getY());
                g_soundEngine->playOnce(SE_APPLE);
                _score++;
                if (_score >= WIN_POINT)
                {
                    setGameState(Lost);
                    _renderer->setLost(true);
                }
                _snake->grow();
                _renderer->updateScore(_score);
            }
        }
                    
        _renderer->refreshSnakeBuffer(_snake->getBufferAsVector());
        timeSinceLastFrameSwap = 0.0f;
    }
}

void Game::processInput()
{
    if (_state == Active)
        _prevDirection = _curDirection;
    _renderer->processInput(_curDirection, _rendererChoice);
    if (_rendererChoice != 0 && _rendererChoice != Gameboard::gameMode)
    {
        _prevState = _state;
        setGameState(SwitchingRenderers);
        return ;
    }
    if (_curDirection == Restart && _state == Lost)
    {
        _state = Restarting;
        return ;
    }
    if (_curDirection == Pause && _state == Active)
    {
        setGameState(Menu);
        _curDirection = None;
    }
    else if (_curDirection == Pause && _state == Menu)
    {
        setGameState(Active);
        _curDirection = _prevDirection;
    }
    if (_curDirection == Exit)
        setGameState(Quit);
}

void Game::render()
{
    if (_renderer != nullptr)
        _renderer->draw();
}

void Game::buildObstacles()
{
    std::vector<float> obstacleXPositions;
    std::vector<float> obstacleYPositions;

    for (int i = 0; i < NUM_OF_OBSTACLES; i++)
    {
        obstacleXPositions.push_back(_obstacles[i]->getX());
        obstacleYPositions.push_back(_obstacles[i]->getY());
    }
    _renderer->buildObstacles(obstacleXPositions, obstacleYPositions);
}

unsigned int Game::getWidth() const { return (Gameboard::windowWidth); }

unsigned int Game::getHeight() const { return (Gameboard::windowHeight); }

unsigned int Game::getRendererChoice() const { return (_rendererChoice); }

GameState Game::getGameState() const { return (_state); }

void Game::setGameState(GameState state) {
    _state = state;
}

void Game::switchRenderer(IRenderer *renderer)
{
    _renderer = renderer;
    _snake->changeRenderer(_renderer);
    _snake->resetBuffer();
    _renderer->setLost(false);
    _renderer->updateApple(_apple->getX(), _apple->getY());
	_renderer->refreshSnakeBuffer(_snake->getBufferAsVector());
    _renderer->updateScore(_score);
    _curDirection = _prevDirection;
    setGameState(_prevState);
    if (_state == Menu)
        _renderer->setPause(true);
    if (_state == Lost)
        _renderer->setLost(true);
}

Game::Game() : _state(Quit), _renderer(nullptr), _snake(nullptr), _apple(nullptr),
    _score(0), _borderOffset(0), _rendererChoice(Gameboard::gameMode), _curDirection(Right)
{

}

Game::Game(Game const & other)
{
    *this = other;
}


Game const & Game::operator=(Game const & rhs)
{
    if (this != &rhs)
    {
        this->_state = rhs._state;
        this->_renderer = rhs._renderer;
        if (this->_snake != nullptr)
            delete _snake;
        this->_snake = new Snake(_renderer);
        this->_snake = rhs._snake;
        if (this->_apple != nullptr)
            delete _apple;
        this->_apple = new RandomlyPlacedObject();
        this->_apple = rhs._apple;

        if (!this->_obstacles.empty())
        {
            for (unsigned int i = 0; i < _obstacles.size(); i++)
                delete _obstacles[i];
        }

        for (unsigned int i = 0; i < rhs._obstacles.size(); i++)
        {
            this->_obstacles.push_back(new RandomlyPlacedObject());
            this->_obstacles[i] = rhs._obstacles[i];
        }

        this->_score = rhs._score;
        this->_borderOffset = rhs._borderOffset;
        this->_rendererChoice = rhs._rendererChoice;
    
        this->_prevDirection = rhs._prevDirection; 
        this->_curDirection = rhs._curDirection;        
    }
    return (*this);
}