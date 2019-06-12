/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RendererB.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:17:05 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/11 16:52:57 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RendererB_HPP
#define RendererB_HPP

#include "IRenderer.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>

//This is the textured 2d renderer. Handles position coordiantes and texture coordinates.

class RendererB: public IRenderer {

private:
	unsigned int _borderOffset;
	unsigned int _score;

	bool _pause;
	std::string _pauseStr;

	float _appleX;
	float _appleY;

    std::ostringstream _ss;

	//static bool _keys[1024];
	static std::unordered_map<std::string, float(*)[12]> _snakeSpriteMap;
	
public:
	RendererB();
	~RendererB();
	
	void refreshSnakeBuffer(std::vector<float> snakeBuffer);

	void buildBorder();
	void buildBackground();

	void updateScore();

	void draw();
	void init();
	bool initGL();
	void cleanupGL();

	void buildApple();
	void updateApple(const float & x, const float & y);


	void processInput(Direction & curDirection);

	void popSnakeTail(std::deque<float> & buffer);
	void buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture);
	void changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture);

	static std::unordered_map<std::string, float(*)[12]> initSnakeSpriteMap();
};

#endif
