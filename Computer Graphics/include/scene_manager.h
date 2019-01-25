#pragma once

#include <memory>
#include <vector>
#include <string>

#include "scene.h"

class scene_manager
{
public:
	static void start(int argc, char* argv[], const std::string& name, int width, int height);

	static void next();
	static void prev();

private:
	static void initialize();
	static void mainLoop();
	static void idle();
	static void cleanup();
	static void resize(int width, int height);

	static void normalKeysDown(unsigned char key, int x, int y);
	static void normalKeysUp(unsigned char key, int x, int y);
	static void specialKeys(int key, int x, int y);
	static void passiveMotion(int x, int y);

	static std::vector<std::unique_ptr<scene>> sceneList;
	static int currentScene;
};