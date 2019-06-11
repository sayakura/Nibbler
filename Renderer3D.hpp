/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer3D.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:09:20 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/10 20:51:31 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP

#include "IRenderer.hpp"

#include <vector>
#include <sstream>

class Renderer3D : public IRenderer {

private:
    bool _pause;
    std::string _pauseStr;

	unsigned int _borderOffset;
	unsigned int _score;

    unsigned int _snakeSize;
    std::deque<float> _snakeCoords;

	float _appleX;
	float _appleY;

    std::ostringstream _ss;

public:
    Renderer3D();
    ~Renderer3D();

    bool initGL();
    void cleanupGL();

    void init();
    void draw();
    void updateApple(const float & x, const float & y);
    void refreshSnakeBuffer(std::vector<float> snakeVertices);
    void processInput(Direction & curDirection);
    void updateScore();
    void buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture);
    void changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture);
    void popSnakeTail(std::deque<float> & buffer);

    void buildBackground();
    void buildApple();
    void buildBorder();
};

#endif