/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:20:49 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/03 21:11:33 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.hpp"
#include "GLDebug.hpp"
#include "ResourceManager.hpp"
#include "VertexArray.hpp"

Renderer::Renderer() : _clearColor(0.0f)
{

}

Renderer::~Renderer()
{
}

void Renderer::drawSprite(Texture & texture, const VertexArray & va, Shader & shader, unsigned int numOfVertices, glm::vec3 color)
{
	shader.bind();
	glm::mat4 model(1.0f);

	shader.setUniformMat4f("u_model", model);
	shader.setUniform3f("u_spriteColor", color.x, color.y, color.z);

	texture.bind(0);
	shader.setUniform1i("u_Image", 0); //might be able to make this call in another function

	va.bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));
}

void Renderer::drawApple(Texture & texture, glm::vec2 pos, const VertexArray & va, Shader & shader, const unsigned int numOfVertices, glm::vec2 size, glm::vec3 color)
{
	shader.bind();
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.setUniformMat4f("u_model", model);
	shader.setUniform3f("u_spriteColor", color.x, color.y, color.z);

	texture.bind();
	shader.setUniform1i("u_Image", 0);

	va.bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));
}

/*void Renderer::draw(const VertexArray & va, unsigned int numOfVertices, const Shader & shader) const
{
	shader.bind();
	va.bind();

	GLCall(glDrawArrays(GL_TRIANGLES, 0, numOfVertices));
}

void Renderer::draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const
{
	shader.bind();
	va.bind();
	ib.bind();

	//everything will be a triangle and ib data should be unsigned int for now
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0));
}*/

void Renderer::clear() const
{
	GLCall(glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	//depth buffer bit for 3d. it's the zbuffer used to recognize what's closer to the screen and should be drawn	
}

void Renderer::setClearColor(glm::vec4 color)
{
	_clearColor = color;
}
