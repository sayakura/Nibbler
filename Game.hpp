/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:11:21 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/11 20:11:22 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
#define GAME_HPP

#include "RandomlyPlacedObject.hpp"
#include "IRenderer.hpp"
#include "Snake.hpp"

enum GameState {
    Active,
    Menu,
    Win,
    Quit
};

class Game {

private:
    GameState _state;
    IRenderer * _renderer;
    Snake *_snake;
    RandomlyPlacedObject *_apple;
    std::vector<RandomlyPlacedObject *> _obstacles;

    unsigned int & _width;
    unsigned int & _height;
    unsigned int &_squareSize;
    unsigned int _score;
    unsigned int _borderOffset;

    Direction _prevDirection;
    Direction _curDirection;

public:
    Game(IRenderer *renderer, unsigned int & width, unsigned int & height, unsigned int & squareSize);
    ~Game();

    void init();
    void processInput(float dt);
    void update(float dt);
    void render();

    void setupObstacles();
    void buildObstacles();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    GameState getGameState() const;

    void setGameState(GameState state);
};

#endif
