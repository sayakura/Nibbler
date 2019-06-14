#include "Quad.hpp"

unsigned int Quad::_offset = 2;
unsigned int Quad::_rows = 6;
unsigned int Quad::_cols = 4;

Quad::Quad()
{
    return;
}

Quad::~Quad()
{
    return;
}

Quad::Quad(Quad const & other)
{
    static_cast<void>(other);
    throw(std::exception());
}

Quad const & Quad::operator=(Quad const & rhs)
{
    throw(std::exception());
    return (rhs);
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

void Quad::buildVertexWithTex(std::vector<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets, float (&texCoords)[12])
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
        for (unsigned int j = 0; j < offsets[1]; j++)
        {
            buffer.push_back(texCoords[texCount]);
            texCount++;
        }
    }
}

void Quad::buildVertexWithTex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets, float (&texCoords)[12])
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
        for (unsigned int j = 0; j < offsets[1]; j++)
        {
            buffer.push_back(texCoords[texCount]);
            texCount++;
        }
    }
}

void Quad::buildVertex(std::vector<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets)
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

void Quad::buildVertex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets)
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
