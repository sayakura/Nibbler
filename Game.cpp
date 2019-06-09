/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kura <Kura@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:19:43 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/09 08:34:02 by Kura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "ResourceManager.hpp"
#include "SnakeSprite.hpp"
#include "sysconfig.hpp"
#include "Quad.hpp"
#include <iostream>
#include <iomanip>

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
    _apple = new AppleMaker(_width, _height, _squareSize);

	while (_snake->checkCollisionPoint(_apple->getX(), _apple->getY()))
		_apple->generateRandomPos();

    _renderer->updateApple(_apple->getX(), _apple->getY());

    //inits the buffer
	_renderer->refreshSnakeBuffer(_snake->getBufferAsVector());
}


void Game::update(float dt)
{
    const float animationSpeed = 15.0f;
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
                _renderer->updateApple(_apple->getX(), _apple->getY());
                g_soundEngine->playOnce(SE_APPLE);
                _snake->grow();
                _renderer->updateScore();
            }
        }
                    
        _renderer->refreshSnakeBuffer(_snake->getBufferAsVector());
        timeSinceLastFrameSwap = 0.0f;
    }

}

void Game::processInput()
{
    _renderer->processInput(_curDirection);
    if (_curDirection == None)
        setGameState(Quit);
}

void Game::render()
{
    if (_renderer != nullptr)
        _renderer->draw();
}

unsigned int Game::getWidth() const { return (_width); }

unsigned int Game::getHeight() const { return (_height); }

GameState Game::getGameState() const { return (_state); }

void Game::setGameState(GameState state)
{
    _state = state;
}
