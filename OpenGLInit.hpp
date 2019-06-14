/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLInit.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:56:36 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:26:40 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLINIT_HPP
#define OPENGLINIT_HPP

#include "glad/glad.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

class OpenGLInit {

public:
    static bool createWindow();
    static void destroyWindow();
    static void clearResources();
    static bool buildShaders(); // only needs to be called once
    static void buildTextures(); // only needs to be called once
    static void enable3dDepth();
    static void disable3dDepth();

    ~OpenGLInit();

private:
    OpenGLInit();
    OpenGLInit(OpenGLInit const &);
    OpenGLInit const & operator=(OpenGLInit const &);
};

#endif