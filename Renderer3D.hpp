/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer3D.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:09:20 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/08 13:45:08 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP

#include "IRenderer.hpp"
#include "VertexArray.hpp"
#include "TextRenderer.hpp"
#include "Camera.hpp"
#include "ObjectDrawingInfo.hpp"

#include "glad/glad.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include <vector>
#include <sstream>

class Renderer3D : public IRenderer {

private:
    Camera _camera;

    ObjectDrawingInfo *_snakeObj;
    ObjectDrawingInfo *_appleObj;
    ObjectDrawingInfo *_border;
    ObjectDrawingInfo *_background;

    TextRenderer *_textRenderer;

	VertexBufferLayout _layout;

    unsigned int _width;
	unsigned int _height;
	unsigned int _squareSize;
	unsigned int _borderOffset;
	unsigned int _score;
	std::vector<unsigned int> _offsets;

    unsigned int _snakeSize;
    std::deque<float> _snakeCoords;
    glm::mat4 _proj;

	float _appleX;
	float _appleY;

    std::ostringstream _ss;

	GLFWwindow *_window;

	static bool _keys[1024];

public:
    Renderer3D(unsigned int width, unsigned int height, unsigned int squareSize);
    ~Renderer3D();

    int initGLFW();
    void allocateDrawObjects();
    bool initResources();

    bool init();
    void draw();
    void updateApple(const float & x, const float & y);
    void refreshSnakeBuffer(std::vector<float> snakeVertices);
    void processInput(Direction & curDirection);
    void updateScore();
    void buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture);
    void changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture);
    void popSnakeTail(std::deque<float> & buffer);

    void drawCube(const VertexArray & va, Shader & shader, unsigned int numOfVertices, glm::vec3 color = glm::vec3(1.0f));
};

#endif