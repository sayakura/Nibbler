/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBufferLayout.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:11:32 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 19:36:42 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#include <vector>
#include <iostream>
#include <assert.h>
#include "glad/glad.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return (sizeof(GLfloat));
            case GL_UNSIGNED_INT: return (sizeof(GLuint));
            case GL_UNSIGNED_BYTE: return (sizeof(GLbyte));
        }
        assert(false);
        return (0);
    }
};

class VertexBufferLayout {

private:
    std::vector<VertexBufferElement> _elements;
    unsigned int _stride;

    template <typename T>
    struct identity { typedef T type; };

    //template specializations weren't working right, so used templated function overloads as a workaround
    //still will be called by the public push function with only one parameter
    template <typename TL>
    void push(unsigned int count, identity<TL>) // specs should be called
    {
        //THIS VERSION SHOULD NEVER GET CALLED
        static_cast<void>(count); 
        return; 
    }

    void push(unsigned int count, identity<float>)
    {
        _elements.push_back({GL_FLOAT, count, GL_FALSE});
        _stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);      
    }

    void push(unsigned int count, identity<unsigned int>)
    {
        _elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        _stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
    }

    void push(unsigned int count, identity<unsigned char>)
    {
        _elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        _stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);        
    }

public:
    VertexBufferLayout() : _stride(0) {}
    ~VertexBufferLayout() { return; }

    template<typename TL>
    void push(unsigned int count)
    {
        push(count, identity<TL>());
    }

    inline const std::vector<VertexBufferElement> & getElements() const { return _elements; }
    inline unsigned int getStride() const { return _stride; }

    VertexBufferLayout(VertexBufferLayout const & other)
    {
        *this = other;
    }

    VertexBufferLayout const & operator=(VertexBufferLayout const & rhs)
    {
        if (this != &rhs)
        {
            this->_elements = rhs._elements;
            this->_stride = rhs._stride;
        }
        return (*this);
    }

};

#endif