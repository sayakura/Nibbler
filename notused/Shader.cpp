/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <dpeck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:33:13 by dpeck             #+#    #+#             */
/*   Updated: 2019/06/13 19:06:17 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GLDebug.hpp"

Shader::Shader() : _rendererID(-1)
{
	return;
}

Shader::Shader(Shader const & other)
{
	*this = other;
}

Shader const & Shader::operator=(Shader const & rhs)
{
	if (this != &rhs)
	{
    	this->_filePath = rhs._filePath;
    	this->_rendererID = rhs._rendererID;
    	this->_uniformLocationCache = rhs._uniformLocationCache;		
	}
	return (*this);
}

Shader::Shader(ShaderProgramSource & source) : _rendererID(0)
{
    _rendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
	//Now deleted with Resource Manager::uncomment if not using resource manager
    //GLCall(glDeleteProgram(_rendererID));
}

void Shader::openGLDelete()
{
    GLCall(glDeleteProgram(_rendererID));	
}

void Shader::bind() const
{
    GLCall(glUseProgram(_rendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string & name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform2f(const std::string & name, float v0, float v1)
{
    GLCall(glUniform2f(getUniformLocation(name), v0, v1));
}

void Shader::setUniform3f(const std::string & name, float v0, float v1, float v2)
{
    GLCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string & name, const glm::mat4 & matrix)
{
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string & name)
{
    if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
        return _uniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(_rendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exit" << std::endl;
    _uniformLocationCache[name] = location;
    return (location);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string & source)
{
	unsigned int id = glCreateShader(type);
	const char * src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	//debugging code to check if compilation succeeded
	int success;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char *message = (char *)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" <<
		(type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << std::endl;
		std::cout << message << std::endl;
	}

	return (id);
}

unsigned int Shader::createShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	int success;
	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
	if (!success)
	{
		int length;
		GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
		char * message = (char *)alloca(length * sizeof(char));
		GLCall(glGetProgramInfoLog(program, length, &length, message));
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << message << std::endl;
	}

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return (program);
}

unsigned int Shader::getID()
{
	return (_rendererID);
}
