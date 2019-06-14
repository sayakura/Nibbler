/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:10:33 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 17:05:07 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.hpp"

unsigned int Cube::_rows = 36;
unsigned int Cube::_cols = 3;
unsigned int Cube::_offset = 3;

std::vector<float> Cube::getGenericCubeCoords()
{
    float cube[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
    return (std::vector<float>(cube, cube + sizeof(cube) / sizeof(float)));
}

std::vector<float> Cube::getCubeAtPos(float x, float y, unsigned int squareSize, unsigned int width, unsigned int height)
{
    float xSize = 2.0f / (width / squareSize);
    float ySize = 2.0f / (height / squareSize);
    y = height - y;
	x = 2.0f * (x) / width - 1.0f;
    y = 2.0f * (y) / height - 1.0f;
    xSize += x;
    ySize += y;

    float cube[] = {
        x, y, 0.0f,
        xSize, y, 0.0f,
        xSize,  ySize, 0.0f,
        xSize,  ySize, 0.0f,
        x,  ySize, 0.0f,
        x, y, 0.0f,

        x, y,  0.1f,
        xSize, y,  0.1f,
        xSize,  ySize,  0.1f,
        xSize,  ySize,  0.1f,
        x,  ySize,  0.1f,
        x, y,  0.1f,

        x,  ySize,  0.1f,
        x,  ySize, 0.0f,
        x, y, 0.0f,
        x, y, 0.0f,
        x, y,  0.1f,
        x,  ySize,  0.1f,

        xSize,  ySize,  0.1f,
        xSize,  ySize, 0.0f,
        xSize, y, 0.0f,
        xSize, y, 0.0f,
        xSize, y,  0.1f,
        xSize,  ySize,  0.1f,

        x, y, 0.0f,
        xSize, y, 0.0f,
        xSize, y,  0.1f,
        xSize, y,  0.1f,
        x, y,  0.1f,
        x, y, 0.0f,

        x,  ySize, 0.0f,
        xSize,  ySize, 0.0f,
        xSize,  ySize,  0.1f,
        xSize,  ySize,  0.1f,
        x,  ySize,  0.1f,
        x,  ySize, 0.0f
    };
    return (std::vector<float>(cube, cube + sizeof(cube) / sizeof(float)));
}

void Cube::buildVertex(std::vector<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets)
{
    int posCount = 0;
    for (unsigned int i = 0; i < Cube::_rows; i++)
    {
        for (unsigned int j = 0; j < offsets[0]; j++)
        {
            buffer.push_back(positions[posCount]);
            posCount++;
        }
    }
}

void Cube::buildVertex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets)
{
    int posCount = 0;
    for (unsigned int i = 0; i < _rows; i++)
    {
        for (unsigned int j = 0; j < offsets[0]; j++)
        {
            buffer.push_back(positions[posCount]);
            posCount++;
        }
    }
}

Cube::Cube()
{
    return;
}

Cube::~Cube()
{
    return;
}

Cube::Cube(Cube const & other)
{
    static_cast<void>(other);
    throw(std::exception());
}

Cube const & Cube::operator=(Cube const & rhs)
{
    throw(std::exception());
    return (rhs);
}