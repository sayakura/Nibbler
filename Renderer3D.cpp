/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer3D.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:12:33 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/10 21:34:00 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer3D.hpp"
#include <iomanip>
#include "Gameboard.hpp"
#include "OpenGLHelper.hpp"
#include "Cube.hpp"

Renderer3D::Renderer3D() :
    _borderOffset(Gameboard::squareSize * 2), _score(0), _snakeSize(0), _pause(false)
{
}

void Renderer3D::init()
{
	buildBackground();
	buildBorder();
	buildApple();

	_ss << std::setfill('0') << std::setw(3) << _score;

	_pauseStr = "-> Continue <-\t   Quit";
}

bool Renderer3D::initGL()
{
	return (OpenGLHelper::initEverything());
}

void Renderer3D::cleanupGL()
{
	OpenGLHelper::cleanup();
}

Renderer3D::~Renderer3D()
{
	return;
}

void Renderer3D::buildBackground()
{
    unsigned int totalRows = Gameboard::windowHeight / Gameboard::squareSize;
    unsigned int totalCols = Gameboard::windowWidth / Gameboard::squareSize;
    unsigned int posX = 0;
    unsigned int posY = 0;

    std::vector<float> cubeCoords;
	std::vector<float> cubeVertices;
    
    for (unsigned int i = 0; i < totalRows; i++)
    {
        posX = 0;
        for (unsigned int j = 0; j < totalCols; j++)
        {
            cubeCoords = Cube::getCubeAtPos(posX, posY, Gameboard::squareSize, Gameboard::windowWidth, Gameboard::windowHeight);
            Cube::buildVertex(cubeVertices, cubeCoords, OpenGLDraw::getBufferFormat(2));
            posX += Gameboard::squareSize;
        }
        posY += Gameboard::squareSize;
    }

	std::cout << "background" << std::endl;
	OpenGLDraw::updateObjectDrawingInfo("background", cubeVertices);
}

void Renderer3D::buildBorder()
{
	unsigned int borderSquare = Gameboard::squareSize;
    unsigned int totalRows = (Gameboard::windowHeight - _borderOffset * 2) / borderSquare;
    unsigned int totalCols = (Gameboard::windowWidth - _borderOffset * 2) / borderSquare;
    unsigned int posX = _borderOffset;
    unsigned int botY = (totalRows) * borderSquare + borderSquare;

    std::vector<float> cubeCoords;
	std::vector<float> borderVertices;
    
    for (unsigned int i = 0; i < totalCols; i++)
    {
        cubeCoords = Cube::getCubeAtPos(posX, _borderOffset, borderSquare, Gameboard::windowWidth, Gameboard::windowHeight);
        Cube::buildVertex(borderVertices, cubeCoords, OpenGLDraw::getBufferFormat(2));
        cubeCoords = Cube::getCubeAtPos(posX, botY, borderSquare, Gameboard::windowWidth, Gameboard::windowHeight);
        Cube::buildVertex(borderVertices, cubeCoords, OpenGLDraw::getBufferFormat(2));
        posX += borderSquare;
    }

    unsigned int rightX = (totalCols) * borderSquare + borderSquare;
    unsigned int posY = _borderOffset + borderSquare;

    for (unsigned int i = 1; i < totalRows; i++)
    {
        cubeCoords = Cube::getCubeAtPos(_borderOffset, posY, borderSquare, Gameboard::windowWidth, Gameboard::windowHeight);
        Cube::buildVertex(borderVertices, cubeCoords, OpenGLDraw::getBufferFormat(2));
        cubeCoords = Cube::getCubeAtPos(rightX, posY, borderSquare, Gameboard::windowWidth, Gameboard::windowHeight);
        Cube::buildVertex(borderVertices, cubeCoords, OpenGLDraw::getBufferFormat(2));
        posY += borderSquare;
    }

	OpenGLDraw::updateObjectDrawingInfo("border", borderVertices);
}

void Renderer3D::buildApple()
{
	std::vector<float> appleCoords = Cube::getGenericCubeCoords();
	OpenGLDraw::updateObjectDrawingInfo("apple", appleCoords);
}

void Renderer3D::draw()
{
	OpenGLDraw::clearScreen();

	float alpha = 1.0f;

	if (_pause)
		alpha = 0.3;

	OpenGLDraw::background(0.0f, 0.0f, 1.0f, 1.0 * alpha);
	OpenGLDraw::border(1.0f, 0.0f, 1.0f, 0.4f * alpha);
	OpenGLDraw::score(_ss.str(), _borderOffset);
	OpenGLDraw::apple(_appleX, _appleY, 1.0f, 0.0f, 0.0f, 1.0f * alpha); // x and y value are unused in this version
	OpenGLDraw::snake(0.0f, 1.0f, 0.0f, 1.0f * alpha);

	if (_pause)
		OpenGLDraw::menu();

	OpenGLDraw::swapBuffers();
}

void Renderer3D::updateApple(const float & x, const float & y)
{
    float inverseY = Gameboard::windowHeight - y;
	this->_appleX = 2.0f * (x) / Gameboard::windowWidth - 1.0f;
    this->_appleY = 2.0f * (inverseY) / Gameboard::windowHeight - 1.0f;

	std::vector<float> cubeCoords = Cube::getCubeAtPos(x, y, Gameboard::squareSize, Gameboard::windowWidth, Gameboard::windowHeight);
	std::vector<float> cubeVertices;
    Cube::buildVertex(cubeVertices, cubeCoords, OpenGLDraw::getBufferFormat(2));
	OpenGLDraw::updateObjectDrawingInfo("apple", cubeVertices);
}

void Renderer3D::refreshSnakeBuffer(std::vector<float> snakeVertices)
{
	OpenGLDraw::updateObjectDrawingInfo("snake", snakeVertices);
}

void Renderer3D::processInput(Direction & curDirection)
{
	if (_pause == false)
	{	
		OpenGLInput::gameInput(curDirection);

		if (curDirection == Pause)
			_pause = true;
	}
	else
	{
		OpenGLInput::menuInput(curDirection, _pauseStr);
		
		if (curDirection == Pause)
			_pause = false;
	}
	
}

void Renderer3D::updateScore()
{
    _ss.str("");
    _score++;
    _ss << std::setfill('0') << std::setw(3) << _score;	    
}

void Renderer3D::buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture)
{
    std::vector<float> startingPositions;
	startingPositions = Cube::getCubeAtPos(x, y, Gameboard::squareSize, Gameboard::windowWidth, Gameboard::windowHeight);
    Cube::buildVertex(buffer, startingPositions, OpenGLDraw::getBufferFormat(2));
}

void Renderer3D::changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture)
{
	return;
}

void Renderer3D::popSnakeTail(std::deque<float> & buffer)
{
	for (unsigned int i = 0; i < Cube::_rows; i++)
	{
		for (unsigned int j = 0; j < Cube::_cols; j++)
			buffer.pop_front();
	}
}