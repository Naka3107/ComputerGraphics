#pragma once

#include <string>
#include <GL/glew.h>

class shader
{
public:
	shader();
	~shader();

	void create(std::string path, GLenum type);

	const GLuint getId() const;

private:
	GLuint _shaderId;
};