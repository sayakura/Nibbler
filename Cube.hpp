/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:09:22 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/06 18:14:44 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>
#include <deque>

class Cube {

public:
    static int _rows;
    static int _offset;
    static int _cols;

    static std::vector<float> getPosCoords(float x, float y, unsigned int size);
    static void buildVertex(std::vector<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets, float (&texCoords)[12]);
    static void buildVertex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets, float (&texCoords)[12]);

private:
    Cube();
};


#endif