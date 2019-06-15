/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 18:09:22 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 17:04:01 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>
#include <deque>

class Cube {

public:
    static unsigned int _rows;
    static unsigned int _offset;
    static unsigned int _cols;

    static std::vector<float> getGenericCubeCoords();
    static std::vector<float> getCubeAtPos(float x, float y, unsigned int size, unsigned int width, unsigned int height);
    static void buildVertex(std::vector<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets);
    static void buildVertex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets);

    ~Cube();

private:
    Cube();
    Cube(Cube const &);
    Cube const & operator=(Cube const &);
};


#endif