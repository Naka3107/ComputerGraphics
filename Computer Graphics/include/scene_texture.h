#pragma once

#include "scene.h"
#include <vector>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

// Escena de prueba para comenzar a trabajar con
// fragment shaders.
class scene_texture : public scene
{
public:
	~scene_texture();

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
	GLuint textureCoordinatesVBO;
	GLuint indicesBuffer;


	GLuint texture1, texture2;

	std::vector<cgmath::vec4> cube = {
		{-3,-3,3,1}, {3,-3,3,1}, {3,3,3,1}, {-3,3,3,1},
		{-3,3,3,1}, {3,3,3,1}, {3,3,-3,1}, {-3,3,-3,1},
		{-3,3,-3,1}, {3,3,-3,1}, {3,-3,-3,1}, {-3,-3,-3,1},
		{-3,-3,-3,1}, {3,-3,-3,1}, {3,-3,3,1}, {-3,-3,3,1},
		{3,-3,3,1}, {3,-3,-3,1}, {3,3,-3,1}, {3,3,3,1},
		{-3,-3,-3,1}, {-3,-3,3,1}, {-3,3,3,1}, {-3,3,-3,1}
	};
	std::vector<unsigned int> indices = { 0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11,12,13,14,12,14,15,16,17,18,16,18,19,20,21,22,20,22,23 };
	
	std::vector<cgmath::vec2> coordinates = {
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0}
	};

	void initializeVector();
	cgmath::mat4 modelMatrix();
	cgmath::mat4 viewMatrix();
	cgmath::mat4 perspectiveMatrix(float width, float height);
	cgmath::mat4 newCube;
	cgmath::mat4 model;
	cgmath::mat4 view;
	cgmath::mat4 perspective;
};

