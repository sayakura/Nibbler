#include "Quad.hpp"

int Quad::_offset = 2;
int Quad::_rows = 6;

Quad::Quad()
{
    return;
}

std::vector<float> Quad::getPosCoords(float x, float y, unsigned int size)
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
}

void Quad::buildVertex(std::vector<float> & buffer, std::vector<float> & positions, float (&texCoords)[12])
{
    int posCount = 0;
    int texCount = 0;
    for (unsigned int i = 0; i < _rows; i++)
    {
        for (unsigned int j = 0; j < _offset; j++)
        {
            buffer.push_back(positions[posCount]);
            posCount++;
        }
        for (unsigned int j = 0; j < _offset; j++)
        {
            buffer.push_back(texCoords[texCount]);
            texCount++;
        }
    }
}

void Quad::buildVertex(std::deque<float> & buffer, std::vector<float> & positions, float (&texCoords)[12])
{
    int posCount = 0;
    int texCount = 0;
    for (unsigned int i = 0; i < _rows; i++)
    {
        for (unsigned int j = 0; j < _offset; j++)
        {
            buffer.push_back(positions[posCount]);
            posCount++;
        }
        for (unsigned int j = 0; j < _offset; j++)
        {
            buffer.push_back(texCoords[texCount]);
            texCount++;
        }
    }
}
