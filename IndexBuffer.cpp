/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IndexBuffer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:32:56 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:21:19 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IndexBuffer.hpp"
#include "GLDebug.hpp"

IndexBuffer::IndexBuffer() : _rendererID(-1), _count(0)
{
    return;
}

IndexBuffer::IndexBuffer(IndexBuffer const & other)
{
    *this = other;
}

IndexBuffer const & IndexBuffer::operator=(IndexBuffer const & rhs)
{
    if (this != &rhs)
    {
        _rendererID = rhs._rendererID;
        _count = rhs._count;
    }
    return (*this);
}

IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int count) : _count(count)
{
    assert(sizeof(unsigned int) == sizeof(GLuint)); // this may not be true on some systems

	GLCall(glGenBuffers(1, &_rendererID));
    //bind "selects" the buffer in order to work on it
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
	//this is what actually puts data into the buffer
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &_rendererID));
}

void IndexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
}

void IndexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::getCount() const
{
    return (this->_count);
}