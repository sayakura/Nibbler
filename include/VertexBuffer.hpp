/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VertexBuffer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:20:44 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/09 12:27:51 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "glad/glad.h"

class VertexBuffer {

private:
    unsigned int _rendererID;

public:
    VertexBuffer(); // cannonical form
    VertexBuffer(const void * data, unsigned int size, GLenum usage);
    ~VertexBuffer();
    VertexBuffer(VertexBuffer const &);
    VertexBuffer const & operator=(VertexBuffer const &);

    void bind() const;
    void unbind() const;
    void updateBufferArray(const void * data, unsigned int size);
};

#endif