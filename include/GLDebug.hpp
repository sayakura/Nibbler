/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GLDebug.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:06:22 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/30 15:11:03 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLDEBUG_HPP
#define GLDEBUG_HPP

#include "glad/glad.h"
#include <cassert>

#define DEBUG

//macro to make debugging code less lines/lighter weight
#ifdef DEBUG
	#define GLCall(x) GLClearError(); x; assert(GLLogCall(#x, __FILE__, __LINE__))
#else
	#define GLCall(x)
#endif

void GLClearError();
bool GLLogCall(const char * function, const char * file, int line);

#endif