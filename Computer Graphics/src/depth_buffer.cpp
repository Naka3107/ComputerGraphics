#include "depth_buffer.h"

#include "ifile.h"
#include <IL/il.h>
#include <iostream>

depth_buffer::depth_buffer() {};

depth_buffer::~depth_buffer() {
	glDeleteFramebuffers(1, &_frameBuffer);
	glDeleteTextures(1, &_depthmap);
};

void depth_buffer::create(int resolution) {

	_resolution = resolution;

	glGenTextures(1, &_depthmap);
	glBindTexture(GL_TEXTURE_2D, _depthmap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_DEPTH_COMPONENT,
		_resolution,
		_resolution,
		0,
		GL_DEPTH_COMPONENT,
		GL_FLOAT,
		nullptr
	);

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);

	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D,
		_depthmap,
		0
	);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
};

void depth_buffer::bind() {	
	int data[4];
	glGetIntegerv(GL_VIEWPORT, data);
	_prev_width = data[2];
	_prev_height = data[3];
	glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
	glViewport(0, 0, _resolution, _resolution);
};

void depth_buffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, _prev_width, _prev_height);
};

void depth_buffer::bindDepthMap() {
	glBindTexture(GL_TEXTURE_2D, _depthmap);
};

void depth_buffer::unbindDepthMap() {
	glBindTexture(GL_TEXTURE_2D, 0);
};
