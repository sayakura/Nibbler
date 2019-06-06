/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 22:37:40 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/04 15:35:58 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "SnakeSprite.hpp"
#include "Quad.hpp"
#include <vector>
#include <deque>

enum Direction {
    Up,
    Left,
    Right,
    Down
};

class Snake {

private:
    unsigned int &_width;
    unsigned int &_height;
    unsigned int _rows;
    unsigned int _cols;
    unsigned int _offset;
    unsigned int _squareSize;
    bool _grow;

    Direction _direction;

    std::deque<std::pair<float, float>> _bodyCoords;
    std::vector<bool> _collisionTable;
    std::deque<float> _snakeBuffer;

public:
    Snake(unsigned int & width, unsigned int & height, unsigned int rows, unsigned int offset, unsigned int squareSize);
    ~Snake();
    //void buildVertex(std::vector<float> & positions, float (&texCoords)[12]);
    void changeTexture(unsigned int idx, float * texCoords);

    std::vector<float> getStart();

    //std::vector<float> getPosCoords(float x, float y, unsigned int size);
    std::vector<float> getBufferAsVector();

    bool moveSnake(Direction direction);
    bool checkCollision(Direction & direction);

	void setBoundsCollision(unsigned int borderOffset);

    void setDirection(Direction direction);
    float * getNewTailDirection();

    void turn(Direction newDirection);
    void forward();

    void grow();

    void updateHead(float (&head)[12], float (&neck)[12]);
    float getHeadX();
    float getHeadY();
	bool checkCollisionPoint(float x, float y);
};

#endif
