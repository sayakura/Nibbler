/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRenderer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:05:07 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/06 19:40:31 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRENDERER_HPP
#define IRENDERER_HPP

#include <vector>
#include <deque>
#include "eDirection.hpp"

class IRenderer {

public:
    //virtual ~IRenderer() = 0;
    virtual void draw() = 0;
    virtual bool init() = 0;
    virtual void updateApple(const float & x, const float & y) = 0;
    virtual void refreshSnakeBuffer(std::vector<float> buffer) = 0;
    virtual void processInput(Direction & curDirection) = 0;
    virtual void updateScore() = 0;
    virtual void buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture) = 0;
    virtual void changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture) = 0;
    virtual	void popSnakeTail(std::deque<float> & buffer) = 0;
};

#endif