#pragma once

#include "scene.h"
#include <vector>
#include "vec2.h"
#include "vec4.h"

// Escena de prueba para comenzar a trabajar con
// fragment shaders.
class scene_circle : public scene
{
public:
	~scene_circle();

	void init();
	void awake();
	void sleep();
	void reset() { }
	void mainLoop();
	void resize(int width, int height);
	void normalKeysDown(unsigned char key) { }
	void normalKeysUp(unsigned char key) { }
	void specialKeys(int key) { }
	void passiveMotion(int x, int y) { }

private:
	GLuint shader_program;

	GLuint vao;
	GLuint positionsVBO;
	GLuint colorsVBO;
	GLuint indicesBuffer;

	void makeCircle();
	std::vector<cgmath::vec2> circlePoints;
	std::vector<unsigned int> indices;
	std::vector<cgmath::vec4> colors;
};