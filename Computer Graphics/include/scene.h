#pragma once

#include <GL/glew.h>

// Scene is an abstract class.
class scene
{
public:
	virtual ~scene() {}

	virtual void init() = 0;
	virtual void awake() = 0;
	virtual void sleep() = 0;
	virtual void reset() = 0;
	virtual void mainLoop() = 0;
	virtual void resize(int width, int height) = 0;
	virtual void normalKeysDown(unsigned char key) = 0;
	virtual void normalKeysUp(unsigned char key) = 0;
	virtual void specialKeys(int key) = 0;
	virtual void passiveMotion(int x, int y) = 0;
};