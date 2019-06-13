/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:09:01 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 15:28:29 by dpeck            ###   ########.fr       */
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
    //updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(_position, _target, _up);
}


// I think i can use this to rotate the camera properly
/*void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw) * cos(glm::radians(_pitch)));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw) * cos(glm::radians(_pitch)));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}*/