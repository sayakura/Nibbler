/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLDraw.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:43:55 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/10 19:23:35 by dpeck            ###   ########.fr       */
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
    static std::shared_ptr<ObjectDrawingInfo> _snakeObj;
    static std::shared_ptr<ObjectDrawingInfo> _appleObj;
    static std::shared_ptr<ObjectDrawingInfo> _border;
    static std::shared_ptr<ObjectDrawingInfo> _background;

    static std::unordered_map<std::string, std::shared_ptr<ObjectDrawingInfo>> _objectMap;

    static std::shared_ptr<TextRenderer> _textRenderer;

    static VertexBufferLayout _layout1;
    static VertexBufferLayout _layout2;
    static VertexBufferLayout _layout3;

	static std::vector<unsigned int> _offsets1;
	static std::vector<unsigned int> _offsets2;
	static std::vector<unsigned int> _offsets3;

    static std::string _pauseStr;

public:
    static std::unordered_map<std::string, std::shared_ptr<ObjectDrawingInfo>> initObjectMap();

    static void buildVertexBufferLayouts();
    static void buildTextRenderer();
    static void updateObjectDrawingInfo(const std::string & name, std::vector<float> vertices);

    static void clearScreen();
    static void swapBuffers();
    
    static void background(float & r, float & g, float & b, float & a);
    static void border(float & r, float & g, float & b, float & a);
    static void score(std::string & scoreNumber, unsigned int & borderOffset);
    static void apple(float & x, float & y, float & r, float & g, float & b, float & a);
    static void snake(float & r, float & g, float & b, float & a);
    static void menu();

private:
    OpenGLDraw();
};

#endif