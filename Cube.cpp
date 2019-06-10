/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:10:33 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/09 16:17:03 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.hpp"

int Cube::_rows = 36;
int Cube::_cols = 3;
int Cube::_offset = 3;


    /*float cube[] = {
        x,          y,          -1.0f,
        x,          y,          1.0f,
        x,          y2,   1.0f,
        x2,   y2,   -1.0f,
        x,          y,         -1.0f,
        x,          y2,   -1.0f,
        x2,   y,          1.0f,
        x,          y,          -1.0f,
        x2,   y,          -1.0f,
        x2,   y2,   -1.0f,
        x2,   y,          -1.0f,
        x,          y,          -1.0f,
        x,          y,          -1.0f,
        x,          y2,    1.0f,
        x,          y2,   -1.0f,
        x2,   y,          1.0f,
        x,          y,          1.0f,
        x,          y,          -1.0f,
        x,          y2,   1.0f,
        x,          y2,   1.0f,
        x2,   y,          1.0f,
        x2,   y2,   1.0f,
        x2,   y,          -1.0f,
        x2,   y2,   -1.0f,
        x2,   y,          -1.0f,
        x2,   y2,   1.0f,
        x2,   y,          1.0f,
        x2,   y2,   1.0f,
        x2,   y2,   -1.0f,
        x,          y2,   -1.0f,
        x2,   y2,   1.0f,
        x,          y2,   -1.0f,
        x,          y2,   1.0f,
        x2,   y2,   1.0f,
        x,          y2,   1.0f,
        x2,   y,          1.0f
    };*/

    /*float cube[] = {
        x, y, -0.5f,
        x2, y, -0.5f,
        x2,  y2, -0.5f,
        x2,  y2, -0.5f,
        x,  y2, -0.5f,
        x, y, -0.5f,

        x, y,  0.5f,
        x2, y,  0.5f,
        x2,  y2,  0.5f,
        x2,  y2,  0.5f,
        x,  y2,  0.5f,
        x, y,  0.5f,

        x,  y2,  0.5f,
        x,  y2, -0.5f,
        x, y, -0.5f,
        x, y, -0.5f,
        x, y,  0.5f,
        x,  y2,  0.5f,

        x2,  y2,  0.5f,
        x2,  y2, -0.5f,
        x2, y, -0.5f,
        x2, y, -0.5f,
        x2, y,  0.5f,
        x2,  y2,  0.5f,

        x, y, -0.5f,
        x2, y, -0.5f,
        x2, y,  0.5f,
        x2, y,  0.5f,
        x, y,  0.5f,
        x, y, -0.5f,

        x,  y2, -0.5f,
        x2,  y2, -0.5f,
        x2,  y2,  0.5f,
        x2,  y2,  0.5f,
        x,  y2,  0.5f,
        x,  y2, -0.5f
};*/

    /*float cube[] = {
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

Cube::Cube()
{
    return;
}*/

std::vector<float> Cube::getGenericCubeCoords()
{
    /*y = 624 - y;
    float ySquareSize = 624 - (y + squareSize);
    x = 2.0f * (x) / 816.0f - 1.0f;
    y = 2.0f * (y) / 624.0f - 1.0f;
    float x2 = 2.0f * (x + squareSize) / 816.0f - 1.0f;
    float y2 = 2.0f * (y + squareSize) / 624.0f - 1.0f;*/

    //float small = squareSize / (624.0f * 816.0f);
    //float big = small + small;

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
    int texCount = 0;
    for (unsigned int i = 0; i < Cube::_rows; i++)
    {
        for (unsigned int j = 0; j < offsets[0]; j++)
        {
            buffer.push_back(positions[posCount]);
            posCount++;
        }
        /*for (unsigned int j = 0; j < offsets[1]; j++)
        {
            buffer.push_back(texCoords[texCount]);
            texCount++;
        }*/
    }
}

void Cube::buildVertex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets)
{
    int posCount = 0;
    int texCount = 0;
    for (unsigned int i = 0; i < _rows; i++)
    {
        for (unsigned int j = 0; j < offsets[0]; j++)
        {
            buffer.push_back(positions[posCount]);
            posCount++;
        }
        /*for (unsigned int j = 0; j < offsets[1]; j++)
        {
            buffer.push_back(texCoords[texCount]);
            texCount++;
        }*/
    }
}