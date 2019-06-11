/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInput.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:15:53 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/10 19:21:15 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLINPUT_HPP
#define OPENGLINPUT_HPP

#include "eDirection.hpp"
#include "GLFW/glfw3.h"
#include <string>

class OpenGLInput {

private:
    static unsigned int _curMenuChoice;

public:
    static void gameInput(Direction & direction);
    static void menuInput(Direction & direction, std::string & pauseStr);
    static void moveCursor(Direction direction, std::string & pauseStr);

private:
    OpenGLInput();

};

#endif