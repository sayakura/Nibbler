/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shapes.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:00:52 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/01 22:25:37 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <deque>

enum ShapeTypes {
    eQuad
};

class Quad {

private:
    static int _rows;
    static int _offset;


public:
    static std::vector<float> getPosCoords(float x, float y, unsigned int size);
    static void buildVertex(std::vector<float> & buffer, std::vector<float> & positions, float (&texCoords)[12]);
    static void buildVertex(std::deque<float> & buffer, std::vector<float> & positions, float (&texCoords)[12]);

private:
    Quad();
};

#endif
