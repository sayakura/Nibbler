/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:05:34 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 19:20:37 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TextRenderer.hpp"
#include "GLDebug.hpp"
#include "ResourceManager.hpp"
#include <iostream>

//TextRenderer from learnGl

TextRenderer::TextRenderer(GLuint width, GLuint height)
{
    this->_textShader = &ResourceManager::getShader("text");
    this->_textShader->bind();
    this->_textShader->setUniformMat4f("u_projection", glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f));
    this->_textShader->setUniform1i("u_text", 0);

    GLCall(glGenVertexArrays(1, &this->_vao));
    GLCall(glGenBuffers(1, &this->_vbo));
    GLCall(glBindVertexArray(this->_vao));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->_vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindVertexArray(0));
}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::load(std::string font, GLuint fontSize)
{
    this->_characters.clear();

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR:: Could not init Freetype Library" << std::endl;
    
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR:: Failed to load font" << std::endl;
    
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

    for (GLubyte c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR:: Failed to load glyph " << c << std::endl;
            continue; 
        }

        GLuint texture;
        GLCall(glGenTextures(1, &texture));
        GLCall(glBindTexture(GL_TEXTURE_2D, texture));
        GLCall(glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        ));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)
        };
        _characters.insert(std::pair<GLchar, Character>(c, character));
    }
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    this->_textShader->bind();
    this->_textShader->setUniform3f("u_textColor", color.x, color.y, color.z);
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindVertexArray(this->_vao));

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = _characters[*c];

        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y + (this->_characters['H'].bearing.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        GLfloat vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 0.0f},
            {xpos, ypos, 0.0f, 0.0f},
            {xpos, ypos + h, 0.0f, 1.0f,},
            {xpos + w, ypos +h, 1.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 0.0f}
        };

        GLCall(glBindTexture(GL_TEXTURE_2D, ch.textureID));

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->_vbo));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));

        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

        x += (ch.advance >> 6) * scale;
    }
    GLCall(glBindVertexArray(0));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

TextRenderer::TextRenderer()
{
    return;
}

TextRenderer::TextRenderer(TextRenderer const & other)
{
    *this = other;
}

TextRenderer const & TextRenderer::operator=(TextRenderer const & rhs)
{
    if (this != &rhs)
    {
        this->_vbo = rhs._vbo;
        this->_vao = rhs._vao;

        this->_textShader = rhs._textShader;
        this->_characters = rhs._characters;
    }
    return (*this);
}