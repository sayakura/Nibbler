/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomlyPlacedObject.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 22:03:03 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/01 22:16:03 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMLYPLACEDOBJECT_HPP
#define RANDOMLYPLACEDOBJECT_HPP

#include <random>

class RandomlyPlacedObject {

private:
    const unsigned int _rows;
    const unsigned int _cols;
    std::pair<float, float> _pos;

    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> rowRange;
    std::uniform_int_distribution<int> colRange;

public:
    RandomlyPlacedObject();
    ~RandomlyPlacedObject();
    RandomlyPlacedObject(RandomlyPlacedObject const &);
    RandomlyPlacedObject const & operator=(RandomlyPlacedObject const &);

    void generateRandomPos();
    float getX();
    float getY();

};

#endif
