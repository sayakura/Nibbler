/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResourceManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:47:19 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 19:00:28 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>

#include "glad/glad.h"

#include "Texture.hpp"
#include "Shader.hpp"

class ResourceManager {

public:
    static std::map<std::string, Shader> _shaders;
    static std::map<std::string, Texture> _textures;
    //static std::map<std::string, IndexBuffer> _indexBuffers;
    //static std::map<std::string, VertexArray> _vertexArrays;

    static Shader & loadShader(const std::string & filePath, const std::string & name);
    static Shader & getShader(const std::string & name);
    static Texture & loadTexture(const std::string & filePath, GLboolean alpha, GLboolean repeat,  const std::string & name);
    static Texture & getTexture(const std::string & name);
    //static IndexBuffer & loadIndexBuffer(const std::string & name);
    //static IndexBuffer & getIndexBuffer(const std::string & name);
    //static VertexArray & loadVertexArray(const std::string & name, unsigned int size);
    //static VertexArray & getVertexArray(const std::string & name);
    static ShaderProgramSource parseShader(const std::string & filePath); // should be moved to private later

    static void clear();

    ~ResourceManager();

private:
    static Texture _texture;
    ResourceManager();
    ResourceManager(ResourceManager const &);
    ResourceManager const & operator=(ResourceManager const &);

    static Texture & loadTextureFromFile(const std::string & filePath, GLboolean alpha, GLboolean repeat);
};

#endif
