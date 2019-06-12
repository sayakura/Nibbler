/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInput.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kura <Kura@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:17:15 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/12 02:55:08 by Kura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLInput.hpp"


unsigned int OpenGLInput::_curMenuChoice = 0;

OpenGLInput::OpenGLInput()
{
    return;
}

void OpenGLInput::gameInput(Direction & curDirection)
{
    glfwPollEvents();

    //handles "X"ing out the window
    if (glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        curDirection = Exit;
        return;
    }

    if (Callback::_keys[GLFW_KEY_UP] && curDirection != Down)
        curDirection = Up;
    else if (Callback::_keys[GLFW_KEY_RIGHT] && curDirection != Left)
        curDirection = Right;
    else if (Callback::_keys[GLFW_KEY_LEFT] && curDirection != Right)
        curDirection = Left;
    else if (Callback::_keys[GLFW_KEY_DOWN] && curDirection != Up)
        curDirection = Down;

    if (Callback::_keys[GLFW_KEY_ESCAPE])
        curDirection = Pause;
}

void OpenGLInput::menuInput(Direction & curDirection, std::string & pauseStr, bool lost)
{
    glfwWaitEvents();

    //handles "X"ing out the window
    if (glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        curDirection = Exit;
        return;
    }

    if (Callback::_keys[GLFW_KEY_LEFT])
    {
        _curMenuChoice = 0;
        moveCursor(Left, pauseStr, lost);
    }
    if (Callback::_keys[GLFW_KEY_RIGHT])
    {
        _curMenuChoice = 1;
        moveCursor(Right, pauseStr, lost);
    }
    if (Callback::_keys[GLFW_KEY_ENTER] && _curMenuChoice == 0)
        curDirection = lost ? Restart : Pause;
    if (Callback::_keys[GLFW_KEY_ENTER] && _curMenuChoice == 1)
        curDirection = Exit;    
}

void OpenGLInput::moveCursor(Direction direction, std::string & pauseStr, bool lost)
{
    if (!lost)
    {
        if (direction == Left)
		    pauseStr = "-> Continue <-\t   Quit";
        if (direction == Right)
            pauseStr = "   Continue   \t-> Quit <-";
    }
    else
    {
        if (direction == Left)
		    pauseStr = "-> Restart <-\t   Quit";
        if (direction == Right)
            pauseStr = "   Restart   \t-> Quit <-";
    }
}