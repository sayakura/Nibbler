/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectDrawingInfo.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 15:35:44 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/07 15:36:44 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTDRAWINGINFO
#define OBJECTDRAWINGINFO

#include <vector>
#include "VertexArray.hpp"

struct ObjectDrawingInfo {

    VertexBuffer *vb;
    VertexArray va;
    std::vector<float> vertices;

	ObjectDrawingInfo() : vb(nullptr) {}
	~ObjectDrawingInfo() { if (vb != nullptr) delete vb; }
};

#endif