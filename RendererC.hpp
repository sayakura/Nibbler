/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RendererC.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:09:20 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/11 18:26:32 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RendererC_HPP
#define RendererC_HPP

#include "IRenderer.hpp"

#include <vector>
#include <sstream>

//This is the 3d renderer. Only takes position coordinates.

class RendererC : public IRenderer {

private:
    bool _pause;
    std::string _pauseStr;

	unsigned int _borderOffset;
	unsigned int _score;

    unsigned int _snakeSize;
    std::deque<float> _snakeCoords;

    bool _obstaclesBuilt;

	float _appleX;
	float _appleY;

    std::ostringstream _ss;

public:
    RendererC();
    ~RendererC();

    bool initGL();
    void cleanupGL();

    bool obstaclesHaveBeenBuilt();
    void buildObstacles(std::vector<float> x, std::vector<float> y);

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