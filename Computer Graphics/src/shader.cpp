#include "shader.h"

#include <iostream>
#include <vector>

#include "ifile.h"

shader::shader()
{
	_shaderId = 0;
}

shader::~shader()
{
	if (_shaderId)
		glDeleteShader(_shaderId);
}

void shader::create(std::string path, GLenum type)
{
	ifile shaderFile;
	if (!shaderFile.read(path)) return;
	std::string source = shaderFile.get_contents();

	if (_shaderId)
		glDeleteShader(_shaderId);

	_shaderId = glCreateShader(type);

	const GLchar *source_c = (const GLchar*)source.c_str();
	glShaderSource(_shaderId, 1, &source_c, nullptr);

	glCompileShader(_shaderId);

	// Get compile status
	GLint shaderCompileSuccess = 0;
	glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &shaderCompileSuccess);
	if (shaderCompileSuccess == GL_FALSE)
	{
		// Get compile log length
		GLint logLength = 0;
		glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{

			// Allocate memory for compile log
			std::vector<GLchar> compileLog(logLength);

			// Get compile log
			glGetShaderInfoLog(_shaderId, logLength, &logLength, compileLog.data());

			// Print compile log
			for (int i = 0; i < logLength; i++)
				std::cout << compileLog[i];
			std::cout << std::endl;
		}
		std::cout << "Shader " << path << " did not compiled." << std::endl;

		//We don't need the shader anymore.
		glDeleteShader(_shaderId);

		return;
	}

	std::cout << "Shader " << path << " compiled successfully" << std::endl;
}

const GLuint shader::getId() const
{
	return _shaderId;
}
