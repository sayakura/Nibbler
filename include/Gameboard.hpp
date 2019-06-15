/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gameboard.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:56:04 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 17:24:56 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

class Gameboard {

public:
    static unsigned int windowWidth;
    static unsigned int windowHeight;
    static unsigned int squareSize;
    static unsigned int gameMode;

    ~Gameboard();

private:
    Gameboard();
    Gameboard(Gameboard const &);
    Gameboard const & operator=(Gameboard const &);
};

#endif