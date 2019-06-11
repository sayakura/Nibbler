/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLDraw.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:43:55 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/10 21:27:03 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGLDRAW_HPP
#define OPENGLDRAW_HPP

#include "glad/glad.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include "ObjectDrawingInfo.hpp"
#include "eDirection.hpp"
#include "TextRenderer.hpp"
#include <vector>
#include <unordered_map>

class OpenGLDraw {

private:
    static ObjectDrawingInfo * _snakeObj;
    static ObjectDrawingInfo * _appleObj;
    static ObjectDrawingInfo * _border;
    static ObjectDrawingInfo * _background;

    static std::unordered_map<std::string, ObjectDrawingInfo *> _objectMap;

    static std::shared_ptr<TextRenderer> _textRenderer;

    static VertexBufferLayout _layouts[3];
    static std::vector<unsigned int> _offsets[3];

    static std::string _pauseStr;

public:
    static std::unordered_map<std::string, ObjectDrawingInfo *> initObjectMap();
    static void allocateObjectDrawingInfo();
    static void destroyObjects();

    static void buildVertexBufferLayouts();
    static void buildTextRenderer();
    static void updateObjectDrawingInfo(const std::string & name, std::vector<float> vertices);

    static void clearScreen();
    static void swapBuffers();
    
    static void background(const float & r, const float & g, const float & b, const float & a);
    static void border(const float & r, const float & g, const float & b, const float & a);
    static void score(const std::string & scoreNumber, unsigned int & borderOffset);
    static void apple(const float & x, const float & y, const float & r, const float & g, const float & b, const float & a);
    static void snake(const float & r, const float & g, const float & b, const float & a);
    static void menu();

    static VertexBufferLayout & getBufferLayout(unsigned int slot);
    static std::vector<unsigned int> & getBufferFormat(unsigned int slot);

private:
    OpenGLDraw();
};

#endif