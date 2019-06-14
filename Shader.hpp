/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:29:32 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 19:08:32 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>
#include "vendor/glm/glm.hpp"

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {

private:
    std::string _filePath;
    unsigned int _rendererID;
    std::unordered_map<std::string, int> _uniformLocationCache;

public:
    Shader();
    Shader(ShaderProgramSource & source);

    Shader(Shader const &);
    Shader const & operator=(Shader const &);
    ~Shader();

    void bind() const;
    void unbind() const;

    void openGLDelete();

    // Set uniforms
    void setUniform1i(const std::string & name, int value);
    void setUniform2f(const std::string & name, float f0, float f1);
    void setUniform3f(const std::string & name, float f0, float f1, float f2);
    void setUniform4f(const std::string & name, float f0, float f1, float f2, float f3);
    void setUniformMat4f(const std::string & name, const glm::mat4 & matrix);
    unsigned int getID();

private:
    ShaderProgramSource parseShader(const std::string & filePath);
    int getUniformLocation(const std::string & name);
    unsigned int createShader(const std::string & vertexShader, const std::string & fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string & source);


};

#endif