#pragma once

#include "scene.h"

class scene_circle_grid : public scene {
public:
	~scene_circle_grid();
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

	int numberOfVertexes = 62;
}; 
