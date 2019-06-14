/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomlyPlacedObject.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 22:05:52 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/14 14:19:09 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RandomlyPlacedObject.hpp"
#include <iostream>
#include "Gameboard.hpp"

RandomlyPlacedObject::RandomlyPlacedObject() :
_rows(Gameboard::windowHeight / Gameboard::squareSize), _cols(Gameboard::windowWidth / Gameboard::squareSize),
rd(), mt(std::mt19937(rd())), rowRange(4, _rows - 5), colRange(4, _cols - 5)
{
	generateRandomPos();
}

RandomlyPlacedObject::~RandomlyPlacedObject()
{
    return;
}

RandomlyPlacedObject::RandomlyPlacedObject(RandomlyPlacedObject const & other) :
_rows(other._rows), _cols(other._cols)
{
    *this = other;
}

RandomlyPlacedObject const & RandomlyPlacedObject::operator=(RandomlyPlacedObject const & rhs)
{
    if (this != &rhs)
    {
        this->_pos = rhs._pos;

        this->mt= rhs.mt;
        this->rowRange = rhs.rowRange;
        this->colRange = rhs.colRange;    
    }
    return (*this);
}

void RandomlyPlacedObject::generateRandomPos()
{
    int x = colRange(mt) * Gameboard::squareSize;
    int y = rowRange(mt) * Gameboard::squareSize;

    _pos.first = static_cast<float>(x);
    _pos.second = static_cast<float>(y);
}

float RandomlyPlacedObject::getX()
{
    return (_pos.first);
}

float RandomlyPlacedObject::getY()
{
    return (_pos.second);
}
