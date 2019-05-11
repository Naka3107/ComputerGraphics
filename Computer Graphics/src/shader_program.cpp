#include "shader_program.h"

#include <iostream>

shader_program::shader_program()
{
	_programId = 0;
}

shader_program::~shader_program()
{
	deleteProgram();
}

void shader_program::create()
{
	_programId = glCreateProgram();
}

void shader_program::attachShader(std::string path, GLenum type)
{
	// Crea un apuntador unico (referencia) a un objeto shader
	std::unique_ptr<shader> shaderReference(new shader);
	// Carga un archivo con codigo de GLSL en la ruta path, con tipo type (GL_VERTEX_SHADER o GL_FRAGMENT_SHADER).
	shaderReference->create(path, type);
	// Agrega la referencia a la lista _attachedShaders
	_attachedShaders.push_back(std::move(shaderReference));
}

void shader_program::link()
{
	for (size_t i = 0; i < _attachedShaders.size(); i++)
		glAttachShader(_programId, _attachedShaders[i]->getId());

	glLinkProgram(_programId);

	// Get status
	GLint linkSuccess = 0;
	glGetProgramiv(_programId, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE)
	{
		// Get link log length
		GLint logLength = 0;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0)
		{
			// Allocate memory for link log
			std::vector<GLchar> linkLog(logLength);

			// Get link log
			glGetProgramInfoLog(_programId, logLength, &logLength, linkLog.data());

			// Print link log
			for (size_t i = 0; i < linkLog.size(); i++)
				std::cout << linkLog[i];
			std::cout << std::endl;
		}
		std::cout << "Shaders could not be linked." << std::endl;

		// Delete and detach shaders; delte program handle
		deleteProgram();

		return;
	}

	std::cout << "Build succeeded... " << std::endl;

	deleteAndDetachShaders();
}

void shader_program::activate()
{
	glUseProgram(_programId);
}

void shader_program::deactivate()
{
	glUseProgram(0);
}

void shader_program::setAttribute(
	GLuint locationIndex,
	std::string name)
{
	glBindAttribLocation(_programId,
		locationIndex,
		name.data());
}

void shader_program::setUniformf(std::string name, float x)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniform1f(uniformLocation, x);
}

void shader_program::setUniformf(std::string name, float x, float y)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniform2f(uniformLocation, x, y);
}

void shader_program::setUniformf(std::string name, cgmath::vec2 value)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniform2fv(uniformLocation, 1, &value[0]);
}

void shader_program::setUniformf(std::string name, float x, float y, float z)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniform3f(uniformLocation, x, y, z);
}

void shader_program::setUniformf(std::string name, cgmath::vec3 value)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniform3fv(uniformLocation, 1, &value[0]);
}

void shader_program::setUniformf(std::string name, float x, float y, float z, float w)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniform4f(uniformLocation, x, y, z, w);
}

void shader_program::setUniformf(std::string name, cgmath::vec4 value)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniform4fv(uniformLocation, 1, &value[0]);
}

void shader_program::setUniformi(std::string name, int value)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniform1i(uniformLocation, value);
}

void shader_program::setUniformMatrix(std::string name, cgmath::mat3 matrix)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
}

void shader_program::setUniformMatrix(std::string name, cgmath::mat4 matrix)
{
	GLint uniformLocation = glGetUniformLocation(_programId, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
}

void shader_program::deleteAndDetachShaders()
{
	for (size_t i = 0; i < _attachedShaders.size(); i++)
		glDetachShader(_programId, _attachedShaders[i]->getId());

	_attachedShaders.clear();
}

void shader_program::deleteProgram()
{
	deleteAndDetachShaders();
	glDeleteProgram(_programId);
}