/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AppleMaker.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 22:05:52 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/09 18:49:56 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AppleMaker.hpp"
#include <iostream>

AppleMaker::AppleMaker(unsigned int & width, unsigned int & height, unsigned int squareSize) :
_width(width), _height(height), _squareSize(squareSize), _rows(height / squareSize), _cols(width / squareSize),
rd(), mt(std::mt19937(rd())), rowRange(4, _rows - 5), colRange(4, _cols - 5)
{
	generateRandomPos();
}

AppleMaker::~AppleMaker()
{
    return;
}

void AppleMaker::generateRandomPos()
{
    int x = colRange(mt) * _squareSize;
    int y = rowRange(mt) * _squareSize;

    _pos.first = static_cast<float>(x);
    _pos.second = static_cast<float>(y);
}

float AppleMaker::getX()
{
    return (_pos.first);
}

float AppleMaker::getY()
{
    return (_pos.second);
}
