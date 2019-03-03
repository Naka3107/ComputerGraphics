#pragma once

#include "scene.h"
#include <vector>
#include "vec2.h"

class scene_chaikin : public scene {
public:
	void init();
	void awake();
	void sleep();
	void reset() { }
	void mainLoop();
	void resize(int width, int height) { }
	void normalKeysDown(unsigned char key);
	void normalKeysUp(unsigned char key) { }
	void specialKeys(int key) { }
	void passiveMotion(int x, int y) { }

private:

	std::vector<std::vector<cgmath::vec2>> segments = {
		{{-0.53f, 0.15f }, {-0.81f, 0.42f }, {-0.91f, 0.73f}},
		{{-0.91f, 0.73f}, {-0.57f, 0.65f}, {-0.27f, 0.32f}}
	};


	GLuint vao[2];
	GLuint positionsVBO[2];
	std::vector<std::vector<cgmath::vec2>> currentSegment;
	
	void initializeSegment(std::vector<std::vector<cgmath::vec2>>& s);
	std::vector<cgmath::vec2> chaikin(std::vector<cgmath::vec2>& v);
	void drawSegment(std::vector<std::vector<cgmath::vec2>>& s);

	
};
