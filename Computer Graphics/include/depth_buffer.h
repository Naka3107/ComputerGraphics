#pragma once

#include <GL/glew.h>

// Escena de prueba para comenzar a trabajar con
// fragment shaders.
class depth_buffer
{
public:
	~depth_buffer();
	depth_buffer();

	void create(int resolution);
	void bind();
	void unbind();
	void bindDepthMap();
	void unbindDepthMap();

private:
	GLuint _frameBuffer = 0;
	GLuint _depthmap = 0;
	GLsizei _resolution = 0;

	int	_prev_width = 0;
	int _prev_height = 0;
}; 
