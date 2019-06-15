/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeSprite.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:00:32 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/01 21:49:43 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKESPRITE_HPP
#define SNAKESPRITE_HPP

namespace SnakeSprite {

static float apple[] = {
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.2f, 0.75f,
    0.0f, 0.0f, 0.0f, 0.75f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.2f, 1.0f,
    1.0f, 0.0f, 0.2f, 0.75f
};

static float rightToDown[] = {
    0.0f, 0.25f,
    0.2f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.25f,
    0.2f, 0.25f,
    0.2f, 0.0f
};

static float horizontal[] = {
    0.2f, 0.25f,
    0.4f, 0.0f,
    0.2f, 0.0f,
    0.2f, 0.25f,
    0.4f, 0.25f,
    0.4f, 0.0f
};

static float leftToDown[] = {
    0.4f, 0.25f,
    0.6f, 0.0f,
    0.4f, 0.0f,
    0.4f, 0.25f,
    0.6f, 0.25f,
    0.6f, 0.0f
};

static float headUp[] = {
    0.6f, 0.25f,
    0.8f, 0.0f,
    0.6f, 0.0f,
    0.6f, 0.25f,
    0.8f, 0.25f,
    0.8f, 0.0f
};

static float headRight[] = {
    0.8f, 0.25f,
    1.0f, 0.0f,
    0.8f, 0.0f,
    0.8f, 0.25f,
    1.0f, 0.25f,
    1.0f, 0.0f
};

static float rightToUp[] = {
    0.0f, 0.5f,
    0.2f, 0.25f,
    0.0f, 0.25f,
    0.0f, 0.5f,
    0.2f, 0.5f,
    0.2f, 0.25f
};

static float vertical[] = {
    0.4f, 0.5f,
    0.6f, 0.25f,
    0.4f, 0.25f,
    0.4f, 0.5f,
    0.6f, 0.5f,
    0.6f, 0.25f
};

static float headLeft[] = {
    0.6f, 0.5f,
    0.8f, 0.25f,
    0.6f, 0.25f,
    0.6f, 0.5f,
    0.8f, 0.5f,
    0.8f, 0.25f
};

static float headDown[] = {
    0.8f, 0.5f,
    1.0f, 0.25f,
    0.8f, 0.25f,
    0.8f, 0.5f,
    1.0f, 0.5f,
    1.0f, 0.25f
};

static float leftToUp[] = {
    0.4f, 0.75f,
    0.6f, 0.5f,
    0.4f, 0.5f,
    0.4f, 0.75f,
    0.6f, 0.75f,
    0.6f, 0.5f
};

static float tailDown[] = {
    0.6f, 0.75f,
    0.8f, 0.5f,
    0.6f, 0.5f,
    0.6f, 0.75f,
    0.8f, 0.75f,
    0.8f, 0.5f
};

static float tailLeft[] = {
    0.8f, 0.75f,
    1.0f, 0.5f,
    0.8f, 0.5f,
    0.8f, 0.75f,
    1.0f, 0.75f,
    1.0f, 0.5f
};

static float tailRight[] = {
    0.6f, 1.0f,
    0.8f, 0.75f,
    0.6f, 0.75f,
    0.6f, 1.0f,
    0.8f, 1.0f,
    0.8f, 0.75f
};

static float tailUp[] = {
    0.8f, 1.0f,
    1.0f, 0.75f,
    0.8f, 0.75f,
    0.8f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.75f
};

}

#endif
