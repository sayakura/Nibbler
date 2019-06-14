/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Callbacks.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:24:03 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 17:00:01 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Callbacks.hpp"
#include <exception>

bool Callback::_keys[1024] = {false};

void Callback::framebufferSizeCallback(GLFWwindow * window, int width, int height)
{
    static_cast<void>(window);
    GLCall(glViewport(0, 0, width, height));
}

void Callback::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
    static_cast<void>(window);
    static_cast<void>(scancode);
    static_cast<void>(action);
    static_cast<void>(mode);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            _keys[key] = true;
        else if (action == GLFW_RELEASE)
            _keys[key] = false;
    }
    return;    
}

//SINGLETON CLASS::SHOULD NEVER BE CREATED, COPIED, OR ASSIGNED
Callback::Callback()
{
    return;
}

Callback::~Callback()
{
    return;
}

Callback::Callback(Callback const & other)
{
    static_cast<void>(other);
    throw(std::exception());
}

Callback const & Callback::operator=(Callback const & rhs)
{
    throw(std::exception());
    return (rhs);
}