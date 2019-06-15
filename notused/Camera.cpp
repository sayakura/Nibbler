/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:09:01 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 17:03:39 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up) :
    _front(glm::vec3(0.0f, 0.0f, -1.0f))
{
    
    _position = position;
    _worldUp = up;
    _up = up;
    _target = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::Camera()
{
    _position = glm::vec3(0.0f);
    _front = glm::vec3(0.0f);
    _up = glm::vec3(0.0f);
    _worldUp = glm::vec3(0.0f);
    _right = glm::vec3(0.0f);
    _target = glm::vec3(0.0f);
}

Camera::~Camera()
{
    return;
}

Camera::Camera(Camera const & other)
{
    *this = other;
}

Camera const & Camera::operator=(Camera const & rhs)
{
    if (this != &rhs)
    {
        _position = rhs._position;
        _front = rhs._front;
        _up = rhs._up;
        _worldUp = rhs._worldUp;
        _right = rhs._right;
        _target = rhs._target;
    }
    return (*this);
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(_position, _target, _up);
}