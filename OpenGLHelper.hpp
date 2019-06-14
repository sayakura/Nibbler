/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLHelper.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:23:57 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:24:48 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLHELPER_HPP
#define OPENGLHELPER_HPP

#include "OpenGLDraw.hpp"
#include "OpenGLInit.hpp"
#include "OpenGLInput.hpp"

//This class connects all OpenGL functions so that only one header file will need to be included
class OpenGLHelper {

public:
    //This calls all gl init/build functions which should only be called once during runtime.
    static bool initEverything();

    //This calls all gl destroy functions which should only be called once during runtime.
    static void cleanup();
    ~OpenGLHelper();

private:
    OpenGLHelper();
    OpenGLHelper(OpenGLHelper const &);
    OpenGLHelper const & operator=(OpenGLHelper const &);

};

#endif