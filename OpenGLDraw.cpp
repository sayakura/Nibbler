/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLDraw.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:23:40 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 18:23:42 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OpenGLDraw.hpp"
#include "Callbacks.hpp"
#include "ResourceManager.hpp"
#include "Camera.hpp"
#include "Gameboard.hpp"

ObjectDrawingInfo * OpenGLDraw::_snakeObj = nullptr;
ObjectDrawingInfo * OpenGLDraw::_appleObj = nullptr;
ObjectDrawingInfo * OpenGLDraw::_border = nullptr;
ObjectDrawingInfo * OpenGLDraw::_background = nullptr;
ObjectDrawingInfo * OpenGLDraw::_obstacles = nullptr;

std::unordered_map<std::string, ObjectDrawingInfo *> OpenGLDraw::_objectMap;

std::shared_ptr<TextRenderer> OpenGLDraw::_textRenderer = nullptr;

VertexBufferLayout OpenGLDraw::_layouts[3];
std::vector<unsigned int> OpenGLDraw::_offsets[3];

std::unordered_map<std::string, ObjectDrawingInfo *> OpenGLDraw::initObjectMap()
{
    std::unordered_map<std::string, ObjectDrawingInfo *> map;
    map["background"] = _background;
    map["border"] = _border;
    map["appleBuild"] = _appleObj;
    map["appleUpdate"] = _appleObj;
    map["obstacles"] = _obstacles;
    map["snake"] = _snakeObj;
    return (map);
}

OpenGLDraw::OpenGLDraw()
{
    return;
}

OpenGLDraw::~OpenGLDraw()
{
    return;
}

OpenGLDraw::OpenGLDraw(OpenGLDraw const & other)
{
    static_cast<void>(other);
    throw(std::exception());
}

OpenGLDraw const & OpenGLDraw::operator=(OpenGLDraw const & rhs)
{
    throw(std::exception());
    return (rhs);
}

void OpenGLDraw::allocateObjectDrawingInfo()
{
    OpenGLDraw::_snakeObj = new ObjectDrawingInfo;
    OpenGLDraw::_appleObj = new ObjectDrawingInfo;
    OpenGLDraw::_background = new ObjectDrawingInfo;
    OpenGLDraw::_border = new ObjectDrawingInfo;
    OpenGLDraw::_obstacles = new ObjectDrawingInfo;

    _objectMap = initObjectMap();
}

void OpenGLDraw::destroyObjects()
{
    if (OpenGLDraw::_snakeObj != nullptr)
        delete _snakeObj;
    if (OpenGLDraw::_appleObj != nullptr)
        delete _appleObj;
    if (OpenGLDraw::_border != nullptr)
        delete _border;
    if (OpenGLDraw::_background != nullptr)
        delete _background;
    if (OpenGLDraw::_obstacles != nullptr)
        delete _obstacles;
}

void OpenGLDraw::resetObjects()
{
    destroyObjects();
    allocateObjectDrawingInfo();
}


void OpenGLDraw::buildTextRenderer()
{
	_textRenderer = static_cast<std::shared_ptr<TextRenderer>>(new TextRenderer(Gameboard::windowWidth, Gameboard::windowHeight));
    _textRenderer->load("fonts/Stencil8bit-Regular.otf", Gameboard::squareSize + Gameboard::squareSize / 2);    
}

void OpenGLDraw::buildVertexBufferLayouts()
{
    //basic 2d
 	_layouts[0].push<float>(2);
	_offsets[0].push_back(2); 

    //2d textured
 	_layouts[1].push<float>(2);
	_offsets[1].push_back(2);
	_layouts[1].push<float>(2);
	_offsets[1].push_back(2);

    //3d version
	_layouts[2].push<float>(3);
	_offsets[2].push_back(3);
}

void OpenGLDraw::updateObjectDrawingInfo(const std::string & name, std::vector<float> & vertices)
{
    ObjectDrawingInfo *obj = _objectMap[name];
    
    obj->vertices = vertices;
    if (name == "appleUpdate")
        obj->vb->updateBufferArray(&obj->vertices[0], obj->vertices.size() * sizeof(float));
    else
    {
        if (obj->vb != nullptr)
            delete obj->vb;
        obj->vb = new VertexBuffer(&obj->vertices[0], obj->vertices.size() * sizeof(float), GL_STATIC_DRAW);
        if (Gameboard::gameMode == 1)
            obj->va.addBuffer(*obj->vb, _layouts[0]);
        else if (Gameboard::gameMode == 2)
            obj->va.addBuffer(*obj->vb, _layouts[1]);
        else if (Gameboard::gameMode == 3)
            obj->va.addBuffer(*obj->vb, _layouts[2]);
    }
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

void OpenGLDraw::background(const float & r, const float & g, const float & b, const float & a)
{
    if (Gameboard::gameMode == 1)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderA");

        shader->bind();
        glm::mat4 model(1.0f);

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);

        _background->va.bind();
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _background->vertices.size()));
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));        
    }
    else if (Gameboard::gameMode == 2)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderB");
        Texture *texture = &ResourceManager::getTexture("grass");

        shader->bind();
        glm::mat4 model(1.0f);

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);

        texture->bind(0);
        shader->setUniform1i("u_Image", 0);

        _background->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _background->vertices.size()));
        texture->unbind();
        shader->unbind();
    }
    else if (Gameboard::gameMode == 3)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderC");

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

void OpenGLDraw::border(const float & r, const float & g, const float & b, const float & a)
{
    if (Gameboard::gameMode == 1)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderA");

     	shader->bind();
        glm::mat4 model(1.0f);
        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);

        _border->va.bind();
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));        
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _border->vertices.size()));
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));        
    }
    else if (Gameboard::gameMode == 2)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderB");
        Texture *texture = &ResourceManager::getTexture("tree");

     	shader->bind();
        glm::mat4 model(1.0f);
        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);
        texture->bind(0);
        shader->setUniform1i("u_Image", 0);

        _border->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _border->vertices.size()));   
        texture->unbind();
        shader->unbind();
    }
    else if (Gameboard::gameMode == 3)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderC");

        shader->bind();
        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.2f));

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);

        _border->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _border->vertices.size()));     
    }
}

void OpenGLDraw::obstacles(const float & r, const float & g, const float & b, const float & a)
{
    if (Gameboard::gameMode == 1)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderA");

     	shader->bind();
        glm::mat4 model(1.0f);
        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);

        _obstacles->va.bind();
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));        
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _obstacles->vertices.size()));
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));        
    }
    else if (Gameboard::gameMode == 2)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderB");
        Texture *texture = &ResourceManager::getTexture("tree");

     	shader->bind();
        glm::mat4 model(1.0f);
        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);
        texture->bind(0);
        shader->setUniform1i("u_Image", 0);

        _obstacles->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _obstacles->vertices.size()));   
        texture->unbind();
        shader->unbind();
    }
    else if (Gameboard::gameMode == 3)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderC");

        shader->bind();
        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.2f));

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);

        _obstacles->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _obstacles->vertices.size()));     
    }
}

void OpenGLDraw::score(const std::string & scoreNumber, unsigned int & borderOffset)
{
    _textRenderer->renderText("Score: " + scoreNumber, borderOffset + 1.0f, borderOffset / 3.0f, 1.0f);    
}

void OpenGLDraw::apple(const float & x, const float & y, const float & r, const float & g, const float & b, const float & a)
{
    if (Gameboard::gameMode == 1)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderA");

        shader->bind();
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(x, y, 0.0f));
        model = glm::scale(model, glm::vec3(static_cast<float>(Gameboard::squareSize), static_cast<float>(Gameboard::squareSize), 1.0f));

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);

        _appleObj->va.bind();
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));   
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _appleObj->vertices.size()));   
        GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));          
    }
    else if (Gameboard::gameMode == 2)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderB");
        Texture *texture = &ResourceManager::getTexture("snake");

        shader->bind();
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(x, y, 0.0f));
        model = glm::scale(model, glm::vec3(static_cast<float>(Gameboard::squareSize), static_cast<float>(Gameboard::squareSize), 1.0f));

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);

        texture->bind();
        shader->setUniform1i("u_Image", 0);

        _appleObj->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _appleObj->vertices.size()));       
        texture->unbind();
        shader->unbind();
    }
    else if (Gameboard::gameMode == 3)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderC");

        shader->bind();
        glm::mat4 model(1.0f);

        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.4f));

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);
        
        _appleObj->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _appleObj->vertices.size()));	        
    }
}

void OpenGLDraw::snake(const float & r, const float & g, const float & b, const float & a)
{
    if (Gameboard::gameMode == 1)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderA");

      	shader->bind();
        glm::mat4 model(1.0f);

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);

        _snakeObj->va.bind();
        //GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));   
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _snakeObj->vertices.size())); 
        //GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));   
    }
    else if (Gameboard::gameMode == 2)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderB");
        Texture *texture = &ResourceManager::getTexture("snake");

      	shader->bind();
        glm::mat4 model(1.0f);

        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_spriteColor", color.x, color.y, color.z, color.w);

        texture->bind(0);
        shader->setUniform1i("u_Image", 0);

        _snakeObj->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _snakeObj->vertices.size()));
        texture->unbind();
        shader->unbind();
    }
    else if (Gameboard::gameMode == 3)
    {
        glm::vec4 color = glm::vec4(r, g, b, a);
        Shader *shader = &ResourceManager::getShader("ShaderC");
        shader->bind();

        glm::mat4 model;
        model = glm::mat4(1.0f);
        shader->setUniformMat4f("u_model", model);
        shader->setUniform4f("u_cubeColor", color.x, color.y, color.z, color.w);

        _snakeObj->va.bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, _snakeObj->vertices.size()));
    }
}

void OpenGLDraw::menu(const std::string & title, const std::string & options)
{
    _textRenderer->renderText(title, Gameboard::windowWidth / 2.3f, Gameboard::windowHeight / 3.0f, 1.0f);
    _textRenderer->renderText(options, Gameboard::windowWidth / 3.7f, Gameboard::windowHeight / 2.3f, 1.0f);    
}

VertexBufferLayout & OpenGLDraw::getBufferLayout(unsigned int slot)
{
    return (_layouts[slot]);
}

std::vector<unsigned int> & OpenGLDraw::getBufferFormat(unsigned int slot)
{
    return (_offsets[slot]);
}