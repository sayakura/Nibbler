/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:11:21 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/05 15:54:27 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
#define GAME_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "AppleMaker.hpp"
#include "Renderer.hpp"
#include "TextRenderer.hpp"

#include <sstream>
#include <vector>

enum GameState {
    Active,
    Menu,
    Win,
    Quit
};

struct ObjectDrawingInfo {

    VertexBuffer *vb;
    VertexArray va;
    std::vector<float> vertices;
};

class Game {

private:
    GameState _state;
    Renderer * _renderer;
    Snake *_snake;
    AppleMaker *_apple;
    TextRenderer *_textRenderer;

    unsigned int & _width;
    unsigned int & _height;
    unsigned int &_squareSize;
	unsigned int _borderOffset;
    unsigned int _score;

    std::ostringstream _ss;

    ObjectDrawingInfo *_snakeObj;
    ObjectDrawingInfo *_appleObj;
    ObjectDrawingInfo *_border;
    ObjectDrawingInfo *_background;
    ObjectDrawingInfo *_text;
    VertexBufferLayout _layout;

    Direction _curDirection;

public:
    bool _keys[1024];
    Game(unsigned int & width, unsigned int & height, unsigned int & squareSize);
    ~Game();

    void init();
    void processInput(float dt);
    void update(float dt);
    void render();

    void refreshSnakeBuffer();

    void buildBorder();
    void buildBackground();

    void updateScore();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    GameState getGameState() const;

    void setGameState(GameState state);
};

#endif
