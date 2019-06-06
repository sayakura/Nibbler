/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IndexBuffer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:32:18 by dpeck             #+#    #+#             */
/*   Updated: 2019/05/30 18:18:48 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

//general note: count = number of elements
//              size = bytes

class IndexBuffer {

private:
    unsigned int _rendererID;
    unsigned int _count;


public:
    IndexBuffer(); // cannonical form
    IndexBuffer(const unsigned int * data, unsigned int count);
    ~IndexBuffer();
    IndexBuffer(IndexBuffer const &);
    IndexBuffer const & operator=(IndexBuffer const &);

    void bind() const;
    void unbind() const;

    unsigned int getCount() const;
};

#endif