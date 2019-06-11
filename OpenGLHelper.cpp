/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLHelper.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:26:35 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/10 19:30:57 by dpeck            ###   ########.fr       */
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
    OpenGLDraw::buildVertexBufferLayouts();
}

void OpenGLHelper::cleanup()
{
    OpenGLInit::clearResources();
    OpenGLInit::destroyWindow();
}