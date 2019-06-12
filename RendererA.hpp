/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RendererA.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 17:11:13 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/11 18:26:58 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERERA_HPP
#define RENDERERA_HPP

#include "IRenderer.hpp"
#include <string>
#include <sstream>

//This is the basic 2d renderer. Only handles position coordinates.

class RendererA : public IRenderer {

	unsigned int _borderOffset;
	unsigned int _score;

	bool _pause;
	std::string _pauseStr;

	float _appleX;
	float _appleY;

    std::ostringstream _ss;
	
public:
	RendererA();
	~RendererA();

    void init();
	bool initGL();

    void buildBorder();
	void buildBackground();
    void buildApple();
	
	void refreshSnakeBuffer(std::vector<float> snakeBuffer);
	void updateScore();
	void updateApple(const float & x, const float & y);

    void popSnakeTail(std::deque<float> & buffer);
	void buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture);
	void changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture);

    void processInput(Direction & curDirection);

	void draw();

	void cleanupGL();
};

#endif