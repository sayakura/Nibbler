/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:40:46 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/31 16:09:21 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "GLDebug.hpp"
#include "glad/glad.h"

class Texture {

private:
    unsigned int _rendererID;
    int _width, _height, _BPP;

public:
    Texture();
    Texture(int width, int height, unsigned char *image, GLint internalFormat, GLboolean repeat);
    Texture(Texture const &);
    Texture const & operator=(Texture const &);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    void openGLDelete();

    int getWidth() const;
    int getHeight() const;
    int getBPP() const;
};

#endif
