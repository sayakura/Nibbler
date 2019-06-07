/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:17:05 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/06 19:28:27 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_HPP
#define RENDERER_HPP


#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "TextRenderer.hpp"
#include "IRenderer.hpp"
#include "Callbacks.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <string>

#include "glad/glad.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

struct ObjectDrawingInfo {

    VertexBuffer *vb;
    VertexArray va;
    std::vector<float> vertices;

	ObjectDrawingInfo() : vb(nullptr) {}
	~ObjectDrawingInfo() { if (vb != nullptr) delete vb; }
};

class Renderer : public IRenderer {

private:
    ObjectDrawingInfo *_snakeObj;
    ObjectDrawingInfo *_appleObj;
    ObjectDrawingInfo *_border;
    ObjectDrawingInfo *_background;

	TextRenderer *_textRenderer;

	VertexBufferLayout _layout;

	glm::vec4 _clearColor;
	unsigned int _width;
	unsigned int _height;
	unsigned int _squareSize;
	unsigned int _borderOffset;
	unsigned int _score;
	std::vector<unsigned int> _offsets;

	float _appleX;
	float _appleY;

    std::ostringstream _ss;

	GLFWwindow *_window;

	//static bool _keys[1024];
	static std::unordered_map<std::string, float(*)[12]> _snakeSpriteMap;
	
public:
	Renderer(unsigned int width, unsigned int height, unsigned int squareSize);
	~Renderer();
	void setClearColor(glm::vec4 color);
	void clear() const;
	void drawSprite(Texture & texture, const VertexArray & va, Shader & shader, unsigned int numOfVertices, glm::vec3 color = glm::vec3(1.0f));
	void drawApple(Texture & texture, glm::vec2 pos, const VertexArray & va, Shader & shader, const unsigned int numOfVertices, glm::vec2 size = glm::vec2(10, 10), glm::vec3 color = glm::vec3(1.0f));
	void refreshSnakeBuffer(std::vector<float> snakeBuffer);

	void buildBorder();
	void buildBackground();

	void updateScore();

	void draw();
	bool init();
	bool initResources();
	void allocateDrawObjects();
	int initGLFW();

	void buildApple();
	void updateApple(const float & x, const float & y);

	//static void framebufferSizeCallback(GLFWwindow * window, int width, int height);
	//static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode);

	void processInput(Direction & curDirection);

	void popSnakeTail(std::deque<float> & buffer);
	void buildSnakeVertex(float x, float y, std::deque<float> & buffer, std::string texture);
	void changeSnakeTexture(bool tail, unsigned int size, std::deque<float> & buffer, std::string texture);

	static std::unordered_map<std::string, float(*)[12]> initSnakeSpriteMap();
};

#endif
