/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRenderer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kura <Kura@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:05:07 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/12 02:43:13 by Kura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRENDERER_HPP
#define IRENDERER_HPP

#include <vector>
#include <deque>
#include "eDirection.hpp"
#include "OpenGLHelper.hpp"

class IRenderer {
public:
    virtual void draw() = 0;
    virtual void init() = 0;
    virtual bool initGL() = 0;
    virtual void cleanupGL() = 0;
    virtual void updateApple(const float & x, const float & y) = 0;
    virtual void refreshSnakeBuffer(std::vector<float> buffer) = 0;
    virtual void processInput(Direction & curDirection, unsigned int & renderer) = 0;
    virtual void updateScore() = 0;
    virtual void buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture) = 0;
    virtual void changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture) = 0;
    virtual	void popSnakeTail(std::deque<float> & buffer) = 0;
    virtual bool obstaclesHaveBeenBuilt() = 0;
    virtual void buildObstacles(std::vector<float> x, std::vector<float> y) = 0;
    virtual void setLost(bool val) = 0;
};

#endif
