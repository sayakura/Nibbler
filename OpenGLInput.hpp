/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInput.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:15:53 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:28:42 by dpeck            ###   ########.fr       */
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

    ~OpenGLInput();

private:
    OpenGLInput();
    OpenGLInput(OpenGLInput const &);
    OpenGLInput const & operator=(OpenGLInput const &);

};

#endif