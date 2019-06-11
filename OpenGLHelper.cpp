/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLHelper.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:26:35 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/10 21:28:41 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLHelper.hpp"

OpenGLHelper::OpenGLHelper()
{
    return;
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