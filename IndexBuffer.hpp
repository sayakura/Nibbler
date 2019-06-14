/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IndexBuffer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:32:18 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:20:52 by dpeck            ###   ########.fr       */
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

    IndexBuffer(const unsigned int * data, unsigned int count);
    ~IndexBuffer();


    void bind() const;
    void unbind() const;

    unsigned int getCount() const;

private:
    IndexBuffer(); // cannonical form
    IndexBuffer(IndexBuffer const &);
    IndexBuffer const & operator=(IndexBuffer const &);
};

#endif