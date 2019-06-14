/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gameboard.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:57:02 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 17:26:54 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Gameboard.hpp"
#include <exception>

unsigned int Gameboard::squareSize = 0;
unsigned int Gameboard::windowHeight = 0;
unsigned int Gameboard::windowWidth = 0;
unsigned int Gameboard::gameMode = 0;

Gameboard::Gameboard()
{
    return;
}

Gameboard::~Gameboard()
{
    return;
}

Gameboard::Gameboard(Gameboard const & other)
{
    static_cast<void>(other);
    throw(std::exception());
}

Gameboard const & Gameboard::operator=(Gameboard const & rhs)
{
    throw(std::exception());
    return (rhs);
}