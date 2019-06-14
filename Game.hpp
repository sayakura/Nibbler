/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:11:21 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 17:07:53 by dpeck            ###   ########.fr       */
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
    Restarting,
    SwitchingRenderers
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
    unsigned int _rendererChoice;
    unsigned int _cannonicalFormDummy;

    Direction _prevDirection;
    Direction _curDirection;

public:
    Game(IRenderer *renderer, unsigned int & width, unsigned int & height, unsigned int & squareSize);
    ~Game();
    Game(Game const &);
    Game const & operator=(Game const &);

    void init();
    void restart();
    void processInput();
    void update(float dt);
    void render();
    void switchRenderer(IRenderer *);

    void setupObstacles();
    void buildObstacles();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getRendererChoice() const;
    GameState getGameState() const;

    void setGameState(GameState state);

private:
    Game();
};

#endif
