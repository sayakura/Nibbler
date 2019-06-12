/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kura <Kura@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:11:21 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/12 02:38:55 by Kura             ###   ########.fr       */
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
    Quit,
    Lost,
    Restarting
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
    void restart();
    void processInput(float dt);
    void update(float dt);
    void render();
    void switchRenderer(IRenderer *);

    void setupObstacles();
    void buildObstacles();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    GameState getGameState() const;

    void setGameState(GameState state);
};

#endif
