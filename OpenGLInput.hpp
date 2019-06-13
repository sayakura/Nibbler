/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInput.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kura <Kura@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:15:53 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/12 05:55:19 by Kura             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLINPUT_HPP
#define OPENGLINPUT_HPP

#include "Callbacks.hpp"
#include "eDirection.hpp"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>

class OpenGLInput {

private:
    static unsigned int _curMenuChoice;

public:
    static void gameInput(Direction & direction);
    static void menuInput(Direction & direction, std::string & pauseStr, bool);
    static void moveCursor(Direction direction, std::string & pauseStr, bool);
    static void rendererSelection(unsigned int & choice);
    //static void getMode(Direction & direction);
private:
    OpenGLInput();

};

#endif