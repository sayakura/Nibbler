/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLDraw.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:23:40 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/10 19:23:32 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLDraw.hpp"
#include "Callbacks.hpp"
#include "ResourceManager.hpp"
#include "Camera.hpp"
#include "sysconfig.hpp"

std::shared_ptr<ObjectDrawingInfo> OpenGLDraw::_snakeObj(new ObjectDrawingInfo);
std::shared_ptr<ObjectDrawingInfo> OpenGLDraw::_appleObj(new ObjectDrawingInfo);
std::shared_ptr<ObjectDrawingInfo> OpenGLDraw::_border(new ObjectDrawingInfo);
std::shared_ptr<ObjectDrawingInfo> OpenGLDraw::_background(new ObjectDrawingInfo);

std::unordered_map<std::string, std::shared_ptr<ObjectDrawingInfo>> OpenGLDraw::_objectMap = initObjectMap();

std::shared_ptr<TextRenderer> OpenGLDraw::_textRenderer = nullptr;

VertexBufferLayout OpenGLDraw::_layout1;
VertexBufferLayout OpenGLDraw::_layout2;
VertexBufferLayout OpenGLDraw::_layout3;

std::string OpenGLDraw::_pauseStr = "-> Continue <-\t   Quit";

std::unordered_map<std::string, std::shared_ptr<ObjectDrawingInfo>> OpenGLDraw::initObjectMap()
{
    std::unordered_map<std::string, std::shared_ptr<ObjectDrawingInfo>> map;
    map["background"] = _background;
    map["border"] = _border;
    map["apple"] = _appleObj;
    map["snake"] = _snakeObj;
    return (map);
}

OpenGLDraw::OpenGLDraw()
{
    return;
}

void OpenGLDraw::buildTextRenderer()
{
	_textRenderer = static_cast<std::shared_ptr<TextRenderer>>(new TextRenderer(g_windowWidth, g_windowHeight));
    _textRenderer->load("fonts/Stencil8bit-Regular.otf", g_squareSize + g_squareSize / 2);    
}

void OpenGLDraw::buildVertexBufferLayouts()
{
    //2d textured
 	_layout2.push<float>(2);
	_offsets2.push_back(2);
	_layout2.push<float>(2);
	_offsets2.push_back(2);

    //3d version
	_layout3.push<float>(3);
	_offsets3.push_back(3);
}

void OpenGLDraw::updateObjectDrawingInfo(const std::string & name, std::vector<float> vertices)
{
    ObjectDrawingInfo *obj = _objectMap[name].get();
    
    if (obj->vb != nullptr)
        delete obj->vb;
    obj->vertices = vertices;
    obj->vb = new VertexBuffer(&obj->vertices[0], obj->vertices.size() * sizeof(float), GL_STATIC_DRAW);
    if (g_gameMode == 1)
        obj->va.addBuffer(*obj->vb, _layout1);
    else if (g_gameMode == 2)
        obj->va.addBuffer(*obj->vb, _layout2);
    else if (g_gameMode == 3)
        obj->va.addBuffer(*obj->vb, _layout3);
}

void OpenGLDraw::clearScreen()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));    
}

void OpenGLDraw::swapBuffers()
{
	glfwSwapBuffers(glfwGetCurrentContext());    
}

void OpenGLDraw::background(float & r, float & g, float & b, float & a)
{
    if (g_gameMode == 2)
    {
        // need to change to vec4 for pause screen
        glm::vec3 color = glm::vec3(r, g, b);
        Shader *shader = &ResourceManager::getShader("default");
        Texture *texture = &ResourceManager::getTexture("grass");

        shader->bind();
        glm::mat4 model(1.0f);

        shader->setUniformMat4f("u_model", model);
        shader->setUniform3f("u_spriteColor", color.x, color.y, color.z);

        texture->bind(0);
        shader->setUniform1i("u_Image", 0);

        _background->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _background->vertices.size()));
    }
    else if (g_gameMode == 3)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("threedimension");

        shader->bind();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));
        shader->setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);
        shader->setUniformMat4f("u_model", model);
        _background->va.bind();
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _background->vertices.size()));
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));        
    }
}

void OpenGLDraw::border(float & r, float & g, float & b, float & a)
{
    if (g_gameMode == 2)
    {
        glm::vec3 color = glm::vec3(r, g, b);
        Shader *shader = &ResourceManager::getShader("default");
        Texture *texture = &ResourceManager::getTexture("tree");

     	shader->bind();
        glm::mat4 model(1.0f);
        shader->setUniformMat4f("u_model", model);
        shader->setUniform3f("u_spriteColor", color.x, color.y, color.z);
        texture->bind(0);
        shader->setUniform1i("u_Image", 0);

        _border->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _border->vertices.size()));   
    }
    else if (g_gameMode == 3)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("threedimension");

        shader->bind();
        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.2f));

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);

        _border->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _border->vertices.size()));     
    }
}

void OpenGLDraw::score(std::string & scoreNumber, unsigned int & borderOffset)
{
    _textRenderer->renderText("Score: " + scoreNumber, borderOffset + 1.0f, borderOffset / 3.0f, 1.0f);    
}

void OpenGLDraw::apple(float & x, float & y, float & r, float & g, float & b, float & a)
{
    if (g_gameMode == 2)
    {
        glm::vec3 color = glm::vec3(r, g, b);
        Shader *shader = &ResourceManager::getShader("default");
        Texture *texture = &ResourceManager::getTexture("snake");

        shader->bind();
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(x, y, 0.0f));
        model = glm::scale(model, glm::vec3(static_cast<float>(g_squareSize), static_cast<float>(g_squareSize), 1.0f));

        shader->setUniformMat4f("u_model", model);
        shader->setUniform3f("u_spriteColor", color.x, color.y, color.z);

        texture->bind();
        shader->setUniform1i("u_Image", 0);

        _appleObj->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _appleObj->vertices.size()));       
    }
    else if (g_gameMode == 3)
    {
        float xScale = 2.0f / (g_windowWidth / g_squareSize);
        float yScale = 2.0f / (g_windowHeight / g_squareSize);
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("threedimension");

        shader->bind();
        glm::mat4 model(1.0f);

        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.4f));

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);

        _appleObj->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _appleObj->vertices.size()));	        
    }
}

void OpenGLDraw::snake(float & r, float & g, float & b, float & a)
{
    if (g_gameMode == 2)
    {
        glm::vec3 color = glm::vec3(r, g, b);
        Shader *shader = &ResourceManager::getShader("default");
        Texture *texture = &ResourceManager::getTexture("snake");

      	shader->bind();
        glm::mat4 model(1.0f);

        shader->setUniformMat4f("u_model", model);
        shader->setUniform3f("u_spriteColor", color.x, color.y, color.z);

        texture->bind(0);
        shader->setUniform1i("u_Image", 0);

        _snakeObj->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _snakeObj->vertices.size()));  
    }
    else if (g_gameMode == 3)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("threedimension");
        shader->bind();

        glm::mat4 model;
        model = glm::mat4(1.0f);
        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);

        _snakeObj->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _snakeObj->vertices.size()));
    }
}

void OpenGLDraw::menu()
{
    _textRenderer->renderText("Pause", g_windowWidth / 2.3f, g_windowHeight / 3.0f, 1.0f);
    _textRenderer->renderText(_pauseStr, g_windowWidth / 3.7f, g_windowHeight / 2.3f, 1.0f);    
}