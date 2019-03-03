#pragma once

#include "scene.h"

class scene_conchoid : public scene {
public:
	void init();
	void awake();
	void sleep();
	void reset() { }
	void mainLoop();
	void resize(int width, int height) { }
	void normalKeysDown(unsigned char key) { }
	void normalKeysUp(unsigned char key) { }
	void specialKeys(int key) { }
	void passiveMotion(int x, int y) { }

private:

	float k1 = 0.5f;
	float k2 = -0.5f;
	float b = 0.2f;
	int sizeOfVector1, sizeOfVector2;
	// Este es el manager de atributos
	GLuint vao1;
	GLuint vao2;
	// Este es el buffer con el atributo
	GLuint positionsVBO1;
	GLuint positionsVBO2;
}; 
