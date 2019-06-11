/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInput.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:17:15 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/10 20:28:29 by dpeck            ###   ########.fr       */
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

void OpenGLInput::menuInput(Direction & curDirection, std::string & pauseStr)
{
    glfwWaitEvents();

    if (Callback::_keys[GLFW_KEY_LEFT])
    {
        _curMenuChoice = 0;
        moveCursor(Left, pauseStr);
    }
    if (Callback::_keys[GLFW_KEY_RIGHT])
    {
        _curMenuChoice = 1;
        moveCursor(Right, pauseStr);
    }
    if (Callback::_keys[GLFW_KEY_ENTER] && _curMenuChoice == 0)
        curDirection = Pause;
    if (Callback::_keys[GLFW_KEY_ENTER] && _curMenuChoice == 1)
        curDirection = Exit;    
}

void OpenGLInput::moveCursor(Direction direction, std::string & pauseStr)
{
	if (direction == Left)
		pauseStr = "-> Continue <-\t   Quit";
	if (direction == Right)
		pauseStr = "   Continue   \t-> Quit <-";
}