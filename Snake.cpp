/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:17:20 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/04 15:36:53 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"
#include <iostream>

Snake::Snake(unsigned int & width, unsigned int & height, unsigned int rows, unsigned int offset, unsigned int squareSize) : 
    _width(width), _height(height), _squareSize(squareSize), _rows(rows), _cols(offset * 2), _offset(offset), _direction(Right), _grow(false)
{
    unsigned int winSize = width * height;
    for (unsigned int i = 0; i < winSize; i++)
        _collisionTable.push_back(false);


    std::vector<float> start = getStart();

    //arbitrary startingPositions. might want to make these constant values somewhere
    std::vector<float> startingPositions;
    startingPositions = Quad::getPosCoords(start[0], start[1], _squareSize);
    _bodyCoords.push_back(std::pair<float, float>(start[0], start[1]));
    Quad::buildVertex(_snakeBuffer, startingPositions, SnakeSprite::tailLeft);
    _collisionTable[_bodyCoords.back().second * _width + _bodyCoords.back().first] = true;

    startingPositions = Quad::getPosCoords(start[2], start[3], _squareSize);
    _bodyCoords.push_back(std::pair<float, float>(start[2], start[3]));
    Quad::buildVertex(_snakeBuffer, startingPositions, SnakeSprite::horizontal);
    _collisionTable[_bodyCoords.back().second * _width + _bodyCoords.back().first] = true;

    startingPositions = Quad::getPosCoords(start[4], start[5], _squareSize);
    _bodyCoords.push_back(std::pair<float, float>(start[4], start[5]));
    Quad::buildVertex(_snakeBuffer, startingPositions, SnakeSprite::horizontal);
    _collisionTable[_bodyCoords.back().second * _width + _bodyCoords.back().first] = true;

    startingPositions = Quad::getPosCoords(start[6], start[7], _squareSize);
    _bodyCoords.push_back(std::pair<float, float>(start[6], start[7]));
    Quad::buildVertex(_snakeBuffer, startingPositions, SnakeSprite::headRight);
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

/*void Snake::buildVertex(std::vector<float> & positions, float (&texCoords)[12])
{
    int posCount = 0;
    int texCount = 0;
    for (unsigned int i = 0; i < _rows; i++)
    {
        for (unsigned int j = 0; j < _offset; j++)
        {
            _snakeBuffer.push_back(positions[posCount]);
            posCount++;
        }
        for (unsigned int j = 0; j < _offset; j++)
        {
            _snakeBuffer.push_back(texCoords[texCount]);
            texCount++;
        }
    }
}*/

void Snake::changeTexture(unsigned int idx, float * texCoords)
{
    int texCount = 0;
    unsigned int curRow = 0;
    if (idx != 0)
        curRow = idx / _cols;
    for (unsigned int i = 0; i < _rows; i++)
    {
        for (unsigned int j = 0; j < _offset; j++)
        {
            _snakeBuffer[curRow * _cols + j + _offset] = texCoords[texCount];
            texCount++;
        }
        curRow++;
    }
}

/*
*       Layout sample:
*       350.0f, 400.0f,
*       400.0f, 350.0f,
*       350.0f, 350.0f,
*       400.0f, 400.0f,
*/
/*std::vector<float> Snake::getPosCoords(float x, float y, unsigned int size)
{
    std::vector<float> quad;

    quad.push_back(x);
    quad.push_back(y + size);

    quad.push_back(x + size);
    quad.push_back(y);

    quad.push_back(x);
    quad.push_back(y);

    quad.push_back(x);
    quad.push_back(y + size);

    quad.push_back(x + size);
    quad.push_back(y + size);

    quad.push_back(x + size);
    quad.push_back(y);
    return (quad);
}*/

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
        for (unsigned int i = 0; i < _rows; i++)
        {
            for (unsigned int j = 0; j < _cols; j++)
                _snakeBuffer.pop_front();
        }
        //this seg faults when out of bounds right now
        _collisionTable[static_cast<int>(_bodyCoords.front().second * _width + _bodyCoords.front().first)] = false;
        _bodyCoords.pop_front();
        float *tailDirection = getNewTailDirection();
        changeTexture(0, tailDirection);
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

float * Snake::getNewTailDirection()
{
    int x1 = static_cast<int>(_bodyCoords[0].first);
    int y1 = static_cast<int>(_bodyCoords[0].second);
    int x2 = static_cast<int>(_bodyCoords[1].first);
    int y2 = static_cast<int>(_bodyCoords[1].second);

    if (x2 - x1 > 0)
        return (SnakeSprite::tailLeft);
    if (x2 - x1 < 0)
        return (SnakeSprite::tailRight);
    if (y2 - y1 < 0)
        return (SnakeSprite::tailDown);
    return (SnakeSprite::tailUp);
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
        updateHead(SnakeSprite::headUp, SnakeSprite::leftToUp);       
    }
    if (_direction == Right && newDirection == Down)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second + _squareSize));
        updateHead(SnakeSprite::headDown, SnakeSprite::leftToDown);        
    }
    if (_direction == Down && newDirection == Left)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first - _squareSize, _bodyCoords.back().second));
        updateHead(SnakeSprite::headLeft, SnakeSprite::leftToUp);        
    }
    if (_direction == Down && newDirection == Right)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first + _squareSize, _bodyCoords.back().second));
        updateHead(SnakeSprite::headRight, SnakeSprite::rightToUp);        
    }
    if (_direction == Left && newDirection == Up)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second - _squareSize));
        updateHead(SnakeSprite::headUp, SnakeSprite::rightToUp);       
    }
    if (_direction == Left && newDirection == Down)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second + _squareSize));
        updateHead(SnakeSprite::headDown, SnakeSprite::rightToDown);        
    }
    if (_direction == Up && newDirection == Left)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first - _squareSize, _bodyCoords.back().second));
        updateHead(SnakeSprite::headLeft, SnakeSprite::leftToDown);       
    }
    if (_direction == Up && newDirection == Right)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first + _squareSize, _bodyCoords.back().second));
        updateHead(SnakeSprite::headRight, SnakeSprite::rightToDown);
    }
}

void Snake::forward()
{
    if (_direction == Right)
    {   
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first + _squareSize, _bodyCoords.back().second));
        updateHead(SnakeSprite::headRight, SnakeSprite::horizontal);
    }
    if (_direction == Left)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first - _squareSize, _bodyCoords.back().second));
        updateHead(SnakeSprite::headLeft, SnakeSprite::horizontal);
    }
    if (_direction == Up)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second - _squareSize));
        updateHead(SnakeSprite::headUp, SnakeSprite::vertical);
    }
    if (_direction == Down)
    {
        _bodyCoords.push_back(std::pair<float, float>(_bodyCoords.back().first, _bodyCoords.back().second + _squareSize));
        updateHead(SnakeSprite::headDown, SnakeSprite::vertical);
    }
}

void Snake::updateHead(float (&head)[12], float (&neck)[12])
{
    //bodyidx locates first idx of vertex with neck information
    unsigned int bodyIdx = (_rows * _cols) * (_bodyCoords.size() - 2);
     changeTexture(bodyIdx, &neck[0]);
     std::vector<float> pos = Quad::getPosCoords(_bodyCoords.back().first, _bodyCoords.back().second, _squareSize);
     Quad::buildVertex(_snakeBuffer, pos, head);
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
