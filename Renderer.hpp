/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:17:05 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/03 21:11:47 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "glad/glad.h"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Snake.hpp"
#include <iostream>
#include <vector>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

class Renderer {

private:
	glm::vec4 _clearColor;
	Shader * _shader;
	glm::mat4 _projection;
	VertexBuffer *_snakeModel;
	VertexArray _va;
	Snake *_snake;
	std::vector<float> _vertices;
	
public:
	Renderer();
	~Renderer();
	void setClearColor(glm::vec4 color);
	void clear() const;
	void drawSprite(Texture & texture, const VertexArray & va, Shader & shader, unsigned int numOfVertices, glm::vec3 color = glm::vec3(1.0f));
	void drawApple(Texture & texture, glm::vec2 pos, const VertexArray & va, Shader & shader, const unsigned int numOfVertices, glm::vec2 size = glm::vec2(10, 10), glm::vec3 color = glm::vec3(1.0f));
	void draw(const VertexArray & va, unsigned int numOfVertices, Shader & shader) const;
	void draw(const VertexArray & va, const IndexBuffer & ib, Shader & shader) const;
};

#endif
