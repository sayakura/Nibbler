/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:17:20 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/06 18:02:23 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"
#include <iostream>

//cols is offset * 2

Snake::Snake(IRenderer * renderer, unsigned int & width, unsigned int & height, unsigned int squareSize) : 
    _renderer(renderer), _width(width), _height(height), _squareSize(squareSize), _direction(Right), _grow(false)
{
    unsigned int winSize = width * height;
    for (unsigned int i = 0; i < winSize; i++)
        _collisionTable.push_back(false);


    std::vector<float> start = getStart();

    //arbitrary startingPositions. might want to make these constant values somewhere

    _bodyCoords.push_back(std::pair<float, float>(start[0], start[1]));
    _renderer->buildSnakeVertex(start[0], start[1], _snakeBuffer, "tailLeft");
    _collisionTable[_bodyCoords.back().second * _width + _bodyCoords.back().first] = true;

    _bodyCoords.push_back(std::pair<float, float>(start[2], start[3]));
    _renderer->buildSnakeVertex(start[2], start[3], _snakeBuffer, "horizontal");
    _collisionTable[_bodyCoords.back().second * _width + _bodyCoords.back().first] = true;

    _bodyCoords.push_back(std::pair<float, float>(start[4], start[5]));
    _renderer->buildSnakeVertex(start[4], start[5], _snakeBuffer, "horizontal");
    _collisionTable[_bodyCoords.back().second * _width + _bodyCoords.back().first] = true;

    _bodyCoords.push_back(std::pair<float, float>(start[6], start[7]));
    _renderer->buildSnakeVertex(start[6], start[7], _snakeBuffer, "headRight");
    _collisionTable[_bodyCoords.back().second * _width + _bodyCoords.back().first] = true;
}

std::vector<float> Snake::getStart()
{
    unsigned int totalRows = _height / _squareSize;
    unsigned int totalCols = _width / _squareSize;
    
    //calculating middle of gameboard based on predefined square/grid size
    int x = (totalCols / 2 - 4) * _squareSize; // offset by 4 so head is in the middle
    int y = (totalRows / 2) * _squareSize;

    std::vector<float> start;
    start.push_back(static_cast<float>(x));
    start.push_back(static_cast<float>(y));
    start.push_back(static_cast<float>(x + _squareSize));
    start.push_back(static_cast<float>(y));
    start.push_back(static_cast<float>(x + _squareSize * 2));
    start.push_back(static_cast<float>(y));
    start.push_back(static_cast<float>(x + _squareSize * 3));
    start.push_back(static_cast<float>(y));
    return (start);
}

//currently set up for tree bounds taking up  two squares on the edge
void Snake::setBoundsCollision(unsigned int borderOffset)
{
	unsigned int topY = borderOffset + _squareSize;
	unsigned int botY = _height - (borderOffset + _squareSize * 2);
	for (unsigned int x = borderOffset; x < _width - borderOffset; x += _squareSize)
	{
		_collisionTable[topY * _width + x] = true;
		_collisionTable[botY * _width + x] = true;
	}
	unsigned int leftX = borderOffset + _squareSize;
	unsigned int rightX = _width - (borderOffset + _squareSize * 2);
	for (unsigned int y = borderOffset; y < _height - borderOffset; y += _squareSize)
	{
		_collisionTable[y * _width + leftX] = true;
		_collisionTable[y * _width + rightX] = true;
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
        _collisionTable[static_cast<int>(_bodyCoords.front().second * _width + _bodyCoords.front().first)] = false;
        _bodyCoords.pop_front();
        std::string tailDirection = getNewTailDirection();
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
        if (_collisionTable[headCoord.second * _width + headCoord.first - _squareSize])
            return (true);
    }
    if (direction == Right)
    {
        if (_collisionTable[headCoord.second * _width + headCoord.first + _squareSize])
            return (true);
    }
    if (direction == Up)
    {
        if (_collisionTable[(headCoord.second - _squareSize) * _width + headCoord.first])
            return (true);
    }
    if (direction == Down)
    {
        if (_collisionTable[(headCoord.second + _squareSize) * _width + headCoord.first])
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
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second - _squareSize));
        updateHead("headUp", "leftToUp");       
    }
    if (_direction == Right && newDirection == Down)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second + _squareSize));
        updateHead("headDown", "leftToDown");        
    }
    if (_direction == Down && newDirection == Left)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first - _squareSize, _bodyCoords.back().second));
        updateHead("headLeft", "leftToUp");        
    }
    if (_direction == Down && newDirection == Right)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first + _squareSize, _bodyCoords.back().second));
        updateHead("headRight", "rightToUp");        
    }
    if (_direction == Left && newDirection == Up)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second - _squareSize));
        updateHead("headUp", "rightToUp");       
    }
    if (_direction == Left && newDirection == Down)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second + _squareSize));
        updateHead("headDown", "rightToDown");        
    }
    if (_direction == Up && newDirection == Left)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first - _squareSize, _bodyCoords.back().second));
        updateHead("headLeft", "leftToDown");       
    }
    if (_direction == Up && newDirection == Right)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first + _squareSize, _bodyCoords.back().second));
        updateHead("headRight", "rightToDown");
    }
}

void Snake::forward()
{
    if (_direction == Right)
    {   
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first + _squareSize, _bodyCoords.back().second));
        updateHead("headRight", "horizontal");
    }
    if (_direction == Left)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first - _squareSize, _bodyCoords.back().second));
        updateHead("headLeft", "horizontal");
    }
    if (_direction == Up)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second - _squareSize));
        updateHead("headUp", "vertical");
    }
    if (_direction == Down)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second + _squareSize));
        updateHead("headDown", "vertical");
    }
}

void Snake::updateHead(const std::string & head, const std::string & neck)
{
    //bodyidx locates first idx of vertex with neck information
    _renderer->changeSnakeTexture(false, _bodyCoords.size(), _snakeBuffer, neck);
    _renderer->buildSnakeVertex(_bodyCoords.back().first, _bodyCoords.back().second, _snakeBuffer, head);
    _collisionTable[_bodyCoords.back().second * _width + _bodyCoords.back().first] = true;
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
	return (_collisionTable[y * _width + x]);
}
