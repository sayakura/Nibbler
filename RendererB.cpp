/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RendererB.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:20:49 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/11 17:41:53 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RendererB.hpp"
#include "Quad.hpp"
#include "SnakeSprite.hpp"
#include "OpenGLHelper.hpp"
#include "Gameboard.hpp"
#include "sysconfig.hpp"
#include <iomanip>

#include <unistd.h>
#include <stdio.h>

extern "C" IRenderer *create_renderer() {
    return new RendererB();
}

std::unordered_map<std::string, float(*)[12]> RendererB::_snakeSpriteMap = RendererB::initSnakeSpriteMap();

std::unordered_map<std::string, float(*)[12]> RendererB::initSnakeSpriteMap()
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

RendererB::RendererB() : 
	_borderOffset(Gameboard::squareSize * 2), _score(0), _pause(false), _lost(false), _obstaclesBuilt(false)
{}

//everything in this class can't be created until GLFW init functions are called
//wanted to maintain the error checking of these functions. so use an init function rather than constructor
void RendererB::init()
{
	buildBackground();
	buildBorder();
	buildApple();

    _score = 0;
    _ss.str("");
	_ss << std::setfill('0') << std::setw(3) << _score;
	_pauseStr = "-> Continue <-\t   Quit";
}

bool RendererB::initGL()
{
	return (OpenGLHelper::initEverything());
}

void RendererB::cleanupGL()
{
	OpenGLHelper::cleanup();
}

RendererB::~RendererB()
{
}

void RendererB::refreshSnakeBuffer(std::vector<float> snakeVertices)
{
	OpenGLDraw::updateObjectDrawingInfo("snake", snakeVertices);
}

void RendererB::buildBackground()
{
     float  texCoords[12] = {0.0f, 1.0f, 
                            1.0f, 0.0f, 
                            0.0f, 0.0f,
                            0.0f, 1.0f,
                            1.0f, 1.0f,
                            1.0f, 0.0f};

	//could try tiling by the texture size instead of the squaresize. doesn't make much of a difference now. but might on a bigger window
    unsigned int totalRows = Gameboard::windowHeight / Gameboard::squareSize;
    unsigned int totalCols = Gameboard::windowWidth / Gameboard::squareSize;
    unsigned int posX = 0;
    unsigned int posY = 0;

    std::vector<float> quadCoords;
	std::vector<float> backgroundVertices;
    
    for (unsigned int i = 0; i < totalRows; i++)
    {
        posX = 0;
        for (unsigned int j = 0; j < totalCols; j++)
        {
            quadCoords = Quad::getPosCoords(posX, posY, Gameboard::squareSize);
            Quad::buildVertexWithTex(backgroundVertices, quadCoords, OpenGLDraw::getBufferFormat(1), texCoords);
            posX += Gameboard::squareSize;
        }
        posY += Gameboard::squareSize;
    }

	OpenGLDraw::updateObjectDrawingInfo("background", backgroundVertices);
}

void RendererB::buildBorder()
{
    float  texCoords[12] = {0.0f, 1.0f, 
                            1.0f, 0.0f, 
                            0.0f, 0.0f,
                            0.0f, 1.0f,
                            1.0f, 1.0f,
                            1.0f, 0.0f};

	unsigned int borderSquare = Gameboard::squareSize * 2;
    unsigned int totalRows = (Gameboard::windowHeight - _borderOffset * 2) / borderSquare;
    unsigned int totalCols = (Gameboard::windowWidth - _borderOffset * 2) / borderSquare;
    unsigned int posX = _borderOffset;
    unsigned int botY = (totalRows) * borderSquare;

    std::vector<float> quadCoords;
	std::vector<float> borderVertices;
    
    for (unsigned int i = 0; i < totalCols; i++)
    {
        quadCoords = Quad::getPosCoords(posX, _borderOffset, borderSquare);
        Quad::buildVertexWithTex(borderVertices, quadCoords, OpenGLDraw::getBufferFormat(1), texCoords);
        quadCoords = Quad::getPosCoords(posX, botY, borderSquare);
        Quad::buildVertexWithTex(borderVertices, quadCoords, OpenGLDraw::getBufferFormat(1), texCoords);
        posX += borderSquare;
    }

    unsigned int rightX = (totalCols) * borderSquare;
    unsigned int posY = _borderOffset + borderSquare;

    for (unsigned int i = 1; i < totalRows; i++)
    {
        quadCoords = Quad::getPosCoords(_borderOffset, posY, borderSquare);
        Quad::buildVertexWithTex(borderVertices, quadCoords, OpenGLDraw::getBufferFormat(1), texCoords);
        quadCoords = Quad::getPosCoords(rightX, posY, borderSquare);
        Quad::buildVertexWithTex(borderVertices, quadCoords, OpenGLDraw::getBufferFormat(1), texCoords);
        posY += borderSquare;
    }

	OpenGLDraw::updateObjectDrawingInfo("border", borderVertices);
}

void RendererB::updateScore()
{
    _ss.str("");
    _score++;
    _ss << std::setfill('0') << std::setw(3) << _score;	
}

void RendererB::draw()
{
	OpenGLDraw::clearScreen();

	float alpha = 1.0f;

	if (_pause || _lost)
		alpha = 0.3;
        
	OpenGLDraw::background(1.0f, 1.0f, 1.0f, 1.0 * alpha);
	OpenGLDraw::border(0.0f, 0.0f, 1.0f, 1.0f * alpha);
    OpenGLDraw::obstacles(1.0f, 0.0f, 1.0f, 1.0f * alpha);
	OpenGLDraw::score(_ss.str(), _borderOffset);
	OpenGLDraw::apple(_appleX, _appleY, 1.0f, 0.0f, 0.0f, 1.0f * alpha); // x and y value are unused in this version
	OpenGLDraw::snake(1.0f, 1.0f, 1.0f, 1.0f * alpha);

	if (_pause)
        OpenGLDraw::menu("Pause", _pauseStr);
    else if (_lost && _score < WIN_POINT)
		OpenGLDraw::menu("Continue ?", _pauseStr);
    else if (_lost)
    {
        g_soundEngine->playOnce(SE_WIN);
        OpenGLDraw::menu("You win !", _pauseStr);
    }
	OpenGLDraw::swapBuffers();
}

void RendererB::buildApple()
{
	std::vector<float> appleVertices(SnakeSprite::apple, SnakeSprite::apple + 4 * 6);
	OpenGLDraw::updateObjectDrawingInfo("appleBuild", appleVertices);
}

void RendererB::updateApple(const float & x, const float & y)
{
	this->_appleX = x;
	this->_appleY = y;
}

void RendererB::processInput(Direction & curDirection)
{
    if (_lost)
    {
        OpenGLInput::menuInput(curDirection, _pauseStr, true);
		
		if (curDirection == Restart)
			_lost = false;
    }
	else if (_pause == false)
	{	
		OpenGLInput::gameInput(curDirection);

		if (curDirection == Pause)
			_pause = true;
	}
	else
	{
		OpenGLInput::menuInput(curDirection, _pauseStr, false);
		
		if (curDirection == Pause)
			_pause = false;
	}
}

void RendererB::buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture)
{
    std::vector<float> startingPositions;
	startingPositions = Quad::getPosCoords(x, y, Gameboard::squareSize);
    Quad::buildVertexWithTex(buffer, startingPositions, OpenGLDraw::getBufferFormat(1), *(RendererB::_snakeSpriteMap[texture]));	
}

void RendererB::changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture)
{
	int idx = (tail) ? 0 : (Quad::_rows * Quad::_cols) * (size - 2);
	float * texCoords = *RendererB::_snakeSpriteMap[texture];
    int texCount = 0;
    unsigned int curRow = 0;
    if (idx != 0)
        curRow = idx / Quad::_cols;
    for (unsigned int i = 0; i < Quad::_rows; i++)
    {
        for (unsigned int j = 0; j < OpenGLDraw::getBufferFormat(1)[1]; j++)
        {
            buffer[curRow * Quad::_cols + j + OpenGLDraw::getBufferFormat(1)[0]] = texCoords[texCount];
            texCount++;
        }
        curRow++;
    }	
}

void RendererB::popSnakeTail(std::deque<float> & buffer)
{
	for (unsigned int i = 0; i < Quad::_rows; i++)
	{
		for (unsigned int j = 0; j < Quad::_cols; j++)
			buffer.pop_front();
	}	
}

bool RendererB::obstaclesHaveBeenBuilt()
{
    return (_obstaclesBuilt);
}

void RendererB::buildObstacles(std::vector<float> x, std::vector<float> y)
{
    float  texCoords[12] = {0.0f, 1.0f, 
                            1.0f, 0.0f, 
                            0.0f, 0.0f,
                            0.0f, 1.0f,
                            1.0f, 1.0f,
                            1.0f, 0.0f};

    std::vector<float> obstacleCoords;

    for (unsigned int i = 0; i < x.size(); i++)
    {
        std::vector<float> obstaclePos = Quad::getPosCoords(x[i], y[i], Gameboard::squareSize);
        Quad::buildVertexWithTex(obstacleCoords, obstaclePos, OpenGLDraw::getBufferFormat(1), texCoords);
    }
    OpenGLDraw::updateObjectDrawingInfo("obstacles", obstacleCoords);
    _obstaclesBuilt = true;
}


void RendererB::setLost(bool val) {
        _lost = val;
        _pauseStr = "-> Restart <-\t   Quit"; }