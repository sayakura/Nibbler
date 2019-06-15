/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexArray.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:26:01 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 19:22:46 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VertexArray.hpp"
#include "GLDebug.hpp"

VertexArray::VertexArray() 
{
    GLCall(glGenVertexArrays(1, &_rendererID));
}

VertexArray::~VertexArray() 
{
    GLCall(glDeleteVertexArrays(1, &_rendererID));
}

VertexArray::VertexArray(VertexArray const & other)
{
    *this = other;
}

VertexArray const & VertexArray::operator=(VertexArray const & rhs)
{
    if (this != &rhs)
    {
        this->_rendererID = rhs._rendererID;
    }
    return (*this);
}

void VertexArray::addBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout)
{
    bind();
    vb.bind();
    const auto & elements = layout.getElements();
    uintptr_t offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto & element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
           layout.getStride(), (void *)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(_rendererID));
}

void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));    
}