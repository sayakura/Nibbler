/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Callbacks.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:24:03 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/06 19:45:43 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Callbacks.hpp"


bool Callback::_keys[1024] = {false};

void Callback::framebufferSizeCallback(GLFWwindow * window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
}

void Callback::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            _keys[key] = true;
        else if (action == GLFW_RELEASE)
            _keys[key] = false;
    }
    return;    
}

Callback::Callback()
{
    return;
}