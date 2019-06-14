/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextRenderer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:04:25 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 19:18:42 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include "ft2build.h"
#include FT_FREETYPE_H
#include "glad/glad.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include <map>

struct Character {
    GLuint textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

class TextRenderer {

private:
    GLuint _vbo;
    GLuint _vao;

public:
    std::map<GLchar, Character> _characters;

    Shader *_textShader;

    TextRenderer(GLuint width, GLuint height);
    ~TextRenderer();

    void load(std::string font, GLuint fontSize);

    void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));

private:
    TextRenderer();
    TextRenderer(TextRenderer const &);
    TextRenderer const & operator=(TextRenderer const &);

};

#endif
