/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 22:37:40 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/14 14:20:18 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "SnakeSprite.hpp"
#include "IRenderer.hpp"
#include "Quad.hpp"
#include "eDirection.hpp"
#include <vector>
#include <deque>

class Snake {

private:
    IRenderer *_renderer;
    bool _grow;

    Direction _direction;

    std::deque<std::pair<float, float>> _bodyCoords;
    std::vector<bool> _collisionTable;
    std::deque<std::string> _whichTexture;
    std::deque<float> _snakeBuffer;

    Snake();

public:
    Snake(IRenderer * renderer);
    ~Snake();
    Snake(Snake const &);
    Snake const & operator=(Snake const &);
    //void buildVertex(std::vector<float> & positions, float (&texCoords)[12]);

    std::vector<float> getStart();

    //std::vector<float> getPosCoords(float x, float y, unsigned int size);
    std::vector<float> getBufferAsVector();

    bool moveSnake(Direction direction);
    bool checkCollision(Direction & direction);

	void setBoundsCollision(unsigned int borderOffset);

    void setDirection(Direction direction);
    std::string getNewTailDirection();

    void turn(Direction newDirection);
    void forward();

    void grow();

    //used when render changes
    void resetBuffer();

    void updateHead(const std::string & head, const std::string & neck);
    float getHeadX();
    float getHeadY();
	bool checkCollisionPoint(float x, float y);
    void setCollisionPoint(float x, float y);

    void changeRenderer(IRenderer *renderer);
};

#endif
