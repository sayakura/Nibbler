/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:17:20 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/14 14:33:40 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"
#include "Gameboard.hpp"
#include <iostream>

//cols is offset * 2

Snake::Snake() : _renderer(nullptr)
{
    return;
}

Snake::Snake(Snake const & other)
{
    *this = other;
}

Snake const & Snake::operator=(Snake const & rhs)
{
    if (this != &rhs)
    {
        this->_renderer = rhs._renderer;
        this->_grow = rhs._grow;

        this->_direction = rhs._direction;

        this->_bodyCoords = rhs._bodyCoords;
        this->_collisionTable = rhs._collisionTable;
        this->_whichTexture = rhs._whichTexture;
        this->_snakeBuffer = rhs._snakeBuffer;       
    }
    return (*this);
}

Snake::Snake(IRenderer * renderer) : 
    _renderer(renderer), _grow(false), _direction(Right)
{
    unsigned int winSize = Gameboard::windowWidth * Gameboard::windowHeight;
    for (unsigned int i = 0; i < winSize; i++)
        _collisionTable.push_back(false);


    std::vector<float> start = getStart();

    //arbitrary startingPositions. might want to make these constant values somewhere

    _bodyCoords.push_back(std::pair<float, float>(start[0], start[1]));
    _renderer->buildSnakeVertex(start[0], start[1], _snakeBuffer, "tailLeft");
    _whichTexture.push_back("tailLeft");
    _collisionTable[_bodyCoords.back().second * Gameboard::windowWidth + _bodyCoords.back().first] = true;

    _bodyCoords.push_back(std::pair<float, float>(start[2], start[3]));
    _renderer->buildSnakeVertex(start[2], start[3], _snakeBuffer, "horizontal");
    _whichTexture.push_back("horizontal");
    _collisionTable[_bodyCoords.back().second * Gameboard::windowWidth + _bodyCoords.back().first] = true;

    _bodyCoords.push_back(std::pair<float, float>(start[4], start[5]));
    _renderer->buildSnakeVertex(start[4], start[5], _snakeBuffer, "horizontal");
    _whichTexture.push_back("horizontal");
    _collisionTable[_bodyCoords.back().second * Gameboard::windowWidth + _bodyCoords.back().first] = true;

    _bodyCoords.push_back(std::pair<float, float>(start[6], start[7]));
    _renderer->buildSnakeVertex(start[6], start[7], _snakeBuffer, "headRight");
    _whichTexture.push_back("headRight");
    _collisionTable[_bodyCoords.back().second * Gameboard::windowWidth + _bodyCoords.back().first] = true;
}

std::vector<float> Snake::getStart()
{
    unsigned int totalRows = Gameboard::windowHeight / Gameboard::squareSize;
    unsigned int totalCols = Gameboard::windowWidth / Gameboard::squareSize;
    
    //calculating middle of gameboard based on predefined square/grid size
    int x = (totalCols / 2 - 4) * Gameboard::squareSize; // offset by 4 so head is in the middle
    int y = (totalRows / 2) * Gameboard::squareSize;

    std::vector<float> start;
    start.push_back(static_cast<float>(x));
    start.push_back(static_cast<float>(y));
    start.push_back(static_cast<float>(x + Gameboard::squareSize));
    start.push_back(static_cast<float>(y));
    start.push_back(static_cast<float>(x + Gameboard::squareSize * 2));
    start.push_back(static_cast<float>(y));
    start.push_back(static_cast<float>(x + Gameboard::squareSize * 3));
    start.push_back(static_cast<float>(y));
    return (start);
}

//currently set up for tree bounds taking up  two squares on the edge
void Snake::setBoundsCollision(unsigned int borderOffset)
{
	unsigned int topY = borderOffset + Gameboard::squareSize;
	unsigned int botY = Gameboard::windowHeight - (borderOffset + Gameboard::squareSize * 2);
	for (unsigned int x = borderOffset; x < Gameboard::windowWidth - borderOffset; x += Gameboard::squareSize)
	{
		_collisionTable[topY * Gameboard::windowWidth + x] = true;
		_collisionTable[botY * Gameboard::windowWidth + x] = true;
	}
	unsigned int leftX = borderOffset + Gameboard::squareSize;
	unsigned int rightX = Gameboard::windowWidth - (borderOffset + Gameboard::squareSize * 2);
	for (unsigned int y = borderOffset; y < Gameboard::windowHeight - borderOffset; y += Gameboard::squareSize)
	{
		_collisionTable[y * Gameboard::windowWidth + leftX] = true;
		_collisionTable[y * Gameboard::windowWidth + rightX] = true;
	}
}

Snake::~Snake()
{
    return;
}

std::vector<float> Snake::getBufferAsVector()
{
    return (std::vector<float>(_snakeBuffer.begin(), _snakeBuffer.end()));
}

bool Snake::moveSnake(Direction direction)
{
    if (checkCollision(direction))
        return (false);

    if (_grow == false)
    {
        _renderer->popSnakeTail(_snakeBuffer);
        //this seg faults when out of bounds right now
        _collisionTable[static_cast<int>(_bodyCoords.front().second * Gameboard::windowWidth + _bodyCoords.front().first)] = false;
        _bodyCoords.pop_front();
        _whichTexture.pop_front();
        std::string tailDirection = getNewTailDirection();
        _whichTexture.front() = tailDirection;
        _renderer->changeSnakeTexture(true, _bodyCoords.size(), _snakeBuffer, tailDirection);
    }

    if (direction != _direction)
    {
        turn(direction);
        setDirection(direction);
    }
    else
        forward();
    
    _grow = false;
    return (true);
}

bool Snake::checkCollision(Direction & direction)
{
    std::pair<float, float> headCoord = _bodyCoords.back();
    if (direction == Left)
    {
        if (_collisionTable[headCoord.second * Gameboard::windowWidth + headCoord.first - Gameboard::squareSize])
            return (true);
    }
    if (direction == Right)
    {
        if (_collisionTable[headCoord.second * Gameboard::windowWidth + headCoord.first + Gameboard::squareSize])
            return (true);
    }
    if (direction == Up)
    {
        if (_collisionTable[(headCoord.second - Gameboard::squareSize) * Gameboard::windowWidth + headCoord.first])
            return (true);
    }
    if (direction == Down)
    {
        if (_collisionTable[(headCoord.second + Gameboard::squareSize) * Gameboard::windowWidth + headCoord.first])
            return (true);
    }
    return (false);
}

void Snake::setDirection(Direction direction)
{
    _direction = direction;
}

std::string Snake::getNewTailDirection()
{
    int x1 = static_cast<int>(_bodyCoords[0].first);
    int y1 = static_cast<int>(_bodyCoords[0].second);
    int x2 = static_cast<int>(_bodyCoords[1].first);
    int y2 = static_cast<int>(_bodyCoords[1].second);

    if (x2 - x1 > 0)
        return ("tailLeft");
    if (x2 - x1 < 0)
        return ("tailRight");
    if (y2 - y1 < 0)
        return ("tailDown");
    return ("tailUp");
}

void Snake::grow()
{
    _grow = true;
}

void Snake::turn(Direction newDirection)
{
    if (_direction == Right && newDirection == Up)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second - Gameboard::squareSize));
        updateHead("headUp", "leftToUp");       
    }
    if (_direction == Right && newDirection == Down)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second + Gameboard::squareSize));
        updateHead("headDown", "leftToDown");        
    }
    if (_direction == Down && newDirection == Left)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first - Gameboard::squareSize, _bodyCoords.back().second));
        updateHead("headLeft", "leftToUp");        
    }
    if (_direction == Down && newDirection == Right)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first + Gameboard::squareSize, _bodyCoords.back().second));
        updateHead("headRight", "rightToUp");        
    }
    if (_direction == Left && newDirection == Up)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second - Gameboard::squareSize));
        updateHead("headUp", "rightToUp");       
    }
    if (_direction == Left && newDirection == Down)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second + Gameboard::squareSize));
        updateHead("headDown", "rightToDown");        
    }
    if (_direction == Up && newDirection == Left)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first - Gameboard::squareSize, _bodyCoords.back().second));
        updateHead("headLeft", "leftToDown");       
    }
    if (_direction == Up && newDirection == Right)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first + Gameboard::squareSize, _bodyCoords.back().second));
        updateHead("headRight", "rightToDown");
    }
}

void Snake::forward()
{
    if (_direction == Right)
    {   
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first + Gameboard::squareSize, _bodyCoords.back().second));
        updateHead("headRight", "horizontal");
    }
    if (_direction == Left)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first - Gameboard::squareSize, _bodyCoords.back().second));
        updateHead("headLeft", "horizontal");
    }
    if (_direction == Up)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second - Gameboard::squareSize));
        updateHead("headUp", "vertical");
    }
    if (_direction == Down)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second + Gameboard::squareSize));
        updateHead("headDown", "vertical");
    }
}

void Snake::updateHead(const std::string & head, const std::string & neck)
{
    //bodyidx locates first idx of vertex with neck information
    _renderer->changeSnakeTexture(false, _bodyCoords.size(), _snakeBuffer, neck);
    _renderer->buildSnakeVertex(_bodyCoords.back().first, _bodyCoords.back().second, _snakeBuffer, head);
    _whichTexture.back() = neck;
    _whichTexture.push_back(head);
    _collisionTable[_bodyCoords.back().second * Gameboard::windowWidth + _bodyCoords.back().first] = true;
}

float Snake::getHeadX()
{
    return (_bodyCoords.back().first);
}

float Snake::getHeadY()
{
    return (_bodyCoords.back().second);
}

bool Snake::checkCollisionPoint(float x, float y)
{
	return (_collisionTable[y * Gameboard::windowWidth + x]);
}

void Snake::setCollisionPoint(float x, float y)
{
    _collisionTable[static_cast<int>(y) * Gameboard::windowWidth + static_cast<int>(x)] = true;
}

void Snake::resetBuffer()
{
    _snakeBuffer.clear();
    for (unsigned int i = 0; i < _bodyCoords.size(); i++)
        _renderer->buildSnakeVertex(_bodyCoords[i].first, _bodyCoords[i].second, _snakeBuffer, _whichTexture[i]);
}

void Snake::changeRenderer(IRenderer * renderer)
{
    this->_renderer = renderer;
}
