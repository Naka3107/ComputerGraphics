#pragma once

#include <memory>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "mat3.h"
#include "mat4.h"
#include "shader.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

class shader_program
{
public:
	shader_program();
	~shader_program();

	void create();
	void attachShader(std::string path, GLenum type);
	void link();

	void activate();
	void deactivate();

	void setAttribute(GLuint locationIndex, std::string name);
	void setUniformf(std::string name, float x);
	void setUniformf(std::string name, float x, float y);
	void setUniformf(std::string name, cgmath::vec2 value);
	void setUniformf(std::string name, float x, float y, float z);
	void setUniformf(std::string name, cgmath::vec3 value);
	void setUniformf(std::string name, float x, float y, float z, float w);
	void setUniformf(std::string name, cgmath::vec4 value);
	void setUniformi(std::string name, int value);
	void setUniformMatrix(std::string name, cgmath::mat3 matrix);
	void setUniformMatrix(std::string name, cgmath::mat4 matrix);

private:
	void deleteAndDetachShaders();
	void deleteProgram();

	GLuint _programId;
	std::vector<std::unique_ptr<shader>> _attachedShaders;
};