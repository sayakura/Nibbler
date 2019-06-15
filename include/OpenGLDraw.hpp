/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLDraw.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:43:55 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:22:01 by dpeck            ###   ########.fr       */
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
    static ObjectDrawingInfo * _obstacles;

    static std::unordered_map<std::string, ObjectDrawingInfo *> _objectMap;

    static std::shared_ptr<TextRenderer> _textRenderer;

    static VertexBufferLayout _layouts[3];
    static std::vector<unsigned int> _offsets[3];
    
public:
    static std::unordered_map<std::string, ObjectDrawingInfo *> initObjectMap();
    static void allocateObjectDrawingInfo();
    static void destroyObjects();
    static void resetObjects();

    static void buildVertexBufferLayouts();
    static void buildTextRenderer();
    static void updateObjectDrawingInfo(const std::string & name, std::vector<float> & vertices);

    static void clearScreen();
    static void swapBuffers();
    
    static void background(const float & r, const float & g, const float & b, const float & a);
    static void border(const float & r, const float & g, const float & b, const float & a);
    static void obstacles(const float & r, const float & g, const float & b, const float & a);
    static void score(const std::string & scoreNumber, unsigned int & borderOffset);
    static void apple(const float & x, const float & y, const float & r, const float & g, const float & b, const float & a);
    static void snake(const float & r, const float & g, const float & b, const float & a);
    static void menu(const std::string & title, const std::string & options);

    static VertexBufferLayout & getBufferLayout(unsigned int slot);
    static std::vector<unsigned int> & getBufferFormat(unsigned int slot);

    ~OpenGLDraw();

private:
    OpenGLDraw();
    OpenGLDraw(OpenGLDraw const &);
    OpenGLDraw const & operator=(OpenGLDraw const &);
};

#endif