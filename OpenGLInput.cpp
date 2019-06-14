/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInput.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:17:15 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:29:38 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLInput.hpp"
#include "sysconfig.hpp"

unsigned int OpenGLInput::_curMenuChoice = 0;

OpenGLInput::OpenGLInput()
{
    return;
}

OpenGLInput::~OpenGLInput()
{
    return;
}

OpenGLInput::OpenGLInput(OpenGLInput const & other)
{
    static_cast<void>(other);
    throw(std::exception());
}

OpenGLInput const & OpenGLInput::operator=(OpenGLInput const & rhs)
{
    throw(std::exception());
    return (rhs);
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

// void OpenGLInput::getMode(Direction & curDirection)
// {
//     glfwPollEvents();
//     if (glfwWindowShouldClose(glfwGetCurrentContext()))
//     {
//         curDirection = Exit;
//         return;
//     }
//     if (Callback::_keys[GLFW_KEY_1])
//         curDirection = Mode1;
//     else if (Callback::_keys[GLFW_KEY_2])
//         curDirection = Mode2;
//     else if (Callback::_keys[GLFW_KEY_3])
//         curDirection = Mode3;
// }


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

void OpenGLInput::rendererSelection(unsigned int & choice)
{
    if (Callback::_keys[GLFW_KEY_1])
        choice = 1;
    if (Callback::_keys[GLFW_KEY_2])
        choice = 2;
    if (Callback::_keys[GLFW_KEY_3])
        choice = 3;
}

void OpenGLInput::moveCursor(Direction direction, std::string & pauseStr, bool lost)
{
    g_soundEngine->playOnce(SE_MENU);
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