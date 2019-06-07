/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:10:33 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/06 18:44:01 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.hpp"

int Cube::_rows = 36;
int Cube::_cols = 3;
int Cube::_offset = 3;

Cube::Cube()
{
    return;
}

std::vector<float> Cube::getPosCoords(float x, float y, unsigned int size)
{
    float cube[] = {
        x,          y,          -1.0f,
        x,          y,          1.0f,
        x,          y + size,   1.0f,
        x + size,   y + size,   -1.0f,
        x,          y,         -1.0f,
        x,          y + size,   -1.0f,
        x + size,   y,          1.0f,
        x,          y,          -1.0f,
        x + size,   y,          -1.0f,
        x + size,   y + size,   -1.0f,
        x + size,   y,          -1.0f,
        x,          y,          -1.0f,
        x,          y,          -1.0f,
        x,          y + size,    1.0f,
        x,          y + size,   -1.0f,
        x + size,   y,          1.0f,
        x,          y,          1.0f,
        x,          y,          -1.0f,
        x,          y + size,   1.0f,
        x,          y + size,   1.0f,
        x + size,   y,          1.0f,
        x + size,   y + size,   1.0f,
        x + size,   y,          -1.0f,
        x + size,   y + size,   -1.0f,
        x + size,   y,          -1.0f,
        x + size,   y + size,   1.0f,
        x + size,   y,          1.0f,
        x + size,   y + size,   1.0f,
        x + size,   y + size,   -1.0f,
        x,          y + size,   -1.0f,
        x + size,   y + size,   1.0f,
        x,          y + size,   -1.0f,
        x,          y + size,   1.0f,
        x + size,   y + size,   1.0f,
        x,          y + size,   1.0f,
        x + size,   y,          1.0f
    };
    return (std::vector<float>(cube, cube + sizeof(cube) / sizeof(float)));
}

void buildVertex(std::vector<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets, float (&texCoords)[12])
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

void Cube::buildVertex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets, float (&texCoords)[12])
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