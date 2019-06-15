/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quad.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:00:52 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:30:38 by dpeck            ###   ########.fr       */
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

public:
    static unsigned int _rows;
    static unsigned int _offset;
    static unsigned int _cols;

    static std::vector<float> getPosCoords(float x, float y, unsigned int size);
    static void buildVertexWithTex(std::vector<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets, float (&texCoords)[12]);
    static void buildVertexWithTex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets, float (&texCoords)[12]);
    static void buildVertex(std::vector<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets);
    static void buildVertex(std::deque<float> & buffer, std::vector<float> & positions, std::vector<unsigned int> & offsets);

    ~Quad();

private:
    Quad();
    Quad(Quad const &);
    Quad const & operator=(Quad const &);
};

#endif
