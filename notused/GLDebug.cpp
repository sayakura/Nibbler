/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GLDebug.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:08:31 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/30 15:12:26 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GLDebug.hpp"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char * function, const char * file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << "0x" << std::hex << error << std::dec <<  "): ";
		std::cout << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}