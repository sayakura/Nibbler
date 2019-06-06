/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:11:21 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/05 21:51:09 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
#define GAME_HPP

#include "AppleMaker.hpp"
#include "Renderer.hpp"
#include "TextRenderer.hpp"
#include <stdio.h>

#include "GLFW/glfw3.h"

#include <vector>

enum GameState {
    Active,
    Menu,
    Win,
    Quit
};

class Game {

private:
    GameState _state;
    Renderer * _renderer;
    Snake *_snake;
    AppleMaker *_apple;

    unsigned int & _width;
    unsigned int & _height;
    unsigned int &_squareSize;
    unsigned int _score;
    unsigned int _borderOffset;

    Direction _curDirection;

public:
    Game(Renderer *renderer, unsigned int & width, unsigned int & height, unsigned int & squareSize);
    ~Game();

    void init();
    void processInput(float dt);
    void update(float dt);
    void render();



    unsigned int getWidth() const;
    unsigned int getHeight() const;
    GameState getGameState() const;

    void setGameState(GameState state);
};

#endif
