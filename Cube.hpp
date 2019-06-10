/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:09:22 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/09 12:49:40 by dpeck            ###   ########.fr       */
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

    static std::vector<float> getGenericCubeCoords();
    static std::vector<float> getCubeAtPos(float x, float y, unsigned int size, unsigned int width, unsigned int height);
    static void buildVertex(std::vector<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets);
    static void buildVertex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets);

private:
    Cube();
};


#endif