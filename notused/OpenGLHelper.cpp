/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLHelper.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:26:35 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:26:10 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLHelper.hpp"

OpenGLHelper::OpenGLHelper()
{
    return;
}

OpenGLHelper::~OpenGLHelper()
{
    return;
}

OpenGLHelper::OpenGLHelper(OpenGLHelper const & other)
{
    static_cast<void>(other);
    throw(std::exception());
}

OpenGLHelper const & OpenGLHelper::operator=(OpenGLHelper const & rhs)
{
    throw(std::exception());
    return (rhs);
}

bool OpenGLHelper::initEverything()
{
    if (OpenGLInit::createWindow() == false)
        return (false);
    if (OpenGLInit::buildShaders() == false)
        return (false);
    OpenGLInit::buildTextures();
    OpenGLDraw::buildTextRenderer();
    OpenGLDraw::allocateObjectDrawingInfo();
    OpenGLDraw::buildVertexBufferLayouts();
    return (true);
}

void OpenGLHelper::cleanup()
{
    OpenGLInit::clearResources();
    OpenGLDraw::destroyObjects();
    OpenGLInit::destroyWindow();
}