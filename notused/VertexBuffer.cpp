/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBuffer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:20:01 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 19:23:26 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VertexBuffer.hpp"
#include "GLDebug.hpp"
#include <iostream>

VertexBuffer::VertexBuffer() : _rendererID(-1)
{

}

VertexBuffer::VertexBuffer(const void * data, unsigned int size, GLenum usage)
{
	GLCall(glGenBuffers(1, &_rendererID));
    //bind "selects" the buffer in order to work on it
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererID));
	//this is what actually puts data into the buffer
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

VertexBuffer::VertexBuffer(VertexBuffer const & other)
{
    *this = other;
}

VertexBuffer const & VertexBuffer::operator=(VertexBuffer const & rhs)
{
    if (this != &rhs)
    {
        this->_rendererID = rhs._rendererID;
    }
    return (*this);
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &_rendererID));
}

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererID));
}

void VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::updateBufferArray(const void * data, unsigned int size)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererID));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}