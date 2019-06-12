/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kura <Kura@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:19:43 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/12 05:45:11 by Kura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "SnakeSprite.hpp"
#include "sysconfig.hpp"
#include "Quad.hpp"
#include <iostream>
#include <iomanip>

#define NUM_OF_OBSTACLES 4

SoundEngine *g_soundEngine;

Game::Game(IRenderer *renderer, unsigned int & width, unsigned int & height, unsigned int & squareSize) :
    _state(Active), _width(width), _height(height), _renderer(renderer),
    _snake(nullptr), _apple(nullptr), _curDirection(Right), _squareSize(squareSize), _score(0)
{
    _borderOffset = _squareSize * 2;
}

Game::~Game()
{
    if (_snake != nullptr)
        delete _snake;
    if (_apple != nullptr)
        delete _apple;
}

void Game::init()
{
    _snake = new Snake(_renderer, _width, _height, _squareSize);
	_snake->setBoundsCollision(_borderOffset);
    _apple = new RandomlyPlacedObject(_width, _height, _squareSize);

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

    _snake = new Snake(_renderer, _width, _height, _squareSize);
	_snake->setBoundsCollision(_borderOffset);
    _apple = new RandomlyPlacedObject(_width, _height, _squareSize);

	while (_snake->checkCollisionPoint(_apple->getX(), _apple->getY()))
		_apple->generateRandomPos();
    
    setupObstacles();    
    _state = Active;
    _renderer->setLost(false);
    _renderer->updateApple(_apple->getX(), _apple->getY());
	_renderer->refreshSnakeBuffer(_snake->getBufferAsVector());
    _score = 0;
    _curDirection = Right;
    _renderer->init();
}

void Game::setupObstacles()
{
    //should change from macro to a variable that's found through the window size.
    for (unsigned int i = 0; i < NUM_OF_OBSTACLES; i++)
    {
        _obstacles.push_back(new RandomlyPlacedObject(_width, _height, _squareSize));
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
                _renderer->updateScore();
            }
        }
                    
        _renderer->refreshSnakeBuffer(_snake->getBufferAsVector());
        timeSinceLastFrameSwap = 0.0f;
    }
}

void Game::processInput(float dt)
{
    //float inputUpdateTime = 1.0f / 5.0f;
    //static float timeSinceLastFrameSwap = 0.0f;
    //timeSinceLastFrameSwap += dt;

    //if (timeSinceLastFrameSwap > inputUpdateTime)
    if (_state == Active)
        _prevDirection = _curDirection;
    _renderer->processInput(_curDirection);
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

unsigned int Game::getWidth() const { return (_width); }

unsigned int Game::getHeight() const { return (_height); }

GameState Game::getGameState() const { return (_state); }

void Game::setGameState(GameState state) {
    _state = state;
}

void Game::switchRenderer(IRenderer *renderer)
{
    _renderer = renderer;
}