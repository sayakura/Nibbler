/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:09:01 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/29 17:44:20 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
    _front(glm::vec3(0.0f, 0.0f, -1.0f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM)
{
    mouse.lastX = XCENTER;
    mouse.lastY = YCENTER;
    mouse.firstMouse = true;
    
    _position = position;
    _worldUp = up;
    _yaw = yaw;
    _pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
    _front(glm::vec3(0.0f, 0.0f, -1.0f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM)
{
    mouse.lastX = XCENTER;
    mouse.lastY = YCENTER;
    mouse.firstMouse = true;

    _position = glm::vec3(posX, posY, posZ);
    _worldUp = glm::vec3(upX, upY, upZ);
    _yaw = yaw;
    _pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(_position, _position + _front, _up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = _movementSpeed * deltaTime;
    if (direction == FORWARD)
        _position += _front * velocity;
    if (direction == BACKWARD)
        _position -= _front * velocity;
    if (direction == LEFT)
        _position -= _right * velocity;
    if (direction == RIGHT)
        _position += _right * velocity;
}

void Camera::processMouseMovement(float xpos, float ypos, GLboolean constrainPitch)
{
    if (mouse.firstMouse)
    {
        mouse.lastX = xpos;
        mouse.lastY = ypos;
        mouse.firstMouse = false;
    }

    float xoffset = xpos - mouse.lastX;
    float yoffset = mouse.lastY - ypos;

    mouse.lastX = xpos;
    mouse.lastY = ypos;

    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw += xoffset;
    _pitch += yoffset;

    if (constrainPitch)
    {
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    if (_zoom >= 1.0f && _zoom <= 45.0f)
        _zoom -= yoffset;
    if (_zoom <= 1.0f)
        _zoom = 1.0f;
    if (_zoom >= 45.0f)
        _zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw) * cos(glm::radians(_pitch)));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw) * cos(glm::radians(_pitch)));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}