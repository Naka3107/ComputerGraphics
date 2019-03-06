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

	std::vector<std::vector<cgmath::vec2>> originalSegment = {
		{{-0.56f, 0.10f }, {-0.79f, 0.35f }, {-0.91f, 0.73f}},
		{{-0.91f, 0.73f}, {-0.57f, 0.61f}, {-0.27f, 0.32f}},
		{{-0.78f, 0.37f}, {-0.81f, 0.61f}, {-0.78f, 0.69f}},    // Left Ear 3
		{{-0.27f, 0.32f}, {-0.003f, 0.39f}, {0.23f, 0.33f}},	// Upper Side Head 4
		{{0.23f, 0.33f}, {0.67f, 0.55f}, {0.95f, 0.61f}},
		{{0.95f, 0.61f}, {0.83f, 0.34f}, {0.72f, 0.22f}, {0.52f, 0.09f}},
		{{0.72f, 0.23f}, {0.80f, 0.39f}, {0.81f, 0.58f}},		// Right Ear 7
		{{-0.53f, 0.15f}, {-0.56f, 0.11f}, {-0.70f, -0.32f}, {-0.53f, -0.59f}, {-0.56f, -0.70f}},  // Left Side Head 8
		{{-0.56f, -0.70f}, {0.71f, -0.70f}},   // Down Side Head 9
		{{0.71f, -0.70f}, {0.69f, -0.44f}, {0.62f, -0.23f}, {0.57f, .03f}, {0.46f, 0.16f}},   // Right Side Head 10
		{{-0.59f, -0.18f}, {-0.52f, -0.18f}, {-0.45f, -0.23f}, {-0.45f, -0.30f}, {-0.51f, -0.34f}, {-0.59f, -0.34f}, {-0.65f, -0.30f}, {-0.65f, -0.23f}, {-0.59f, -0.18f}},     // Left Cheek 11
		{{0.35f, -0.19f}, {0.44f, -0.19f}, {0.51f, -0.24f}, {0.51f, -0.31f}, {0.44f, -0.37f}, {0.36f, -0.37f}, {0.29f, -0.32f}, {0.29f, -0.24f}, {0.35f, -0.19f}},		// Right Cheek 12
		{{-0.40f, 0.005f}, {-0.36f, 0.04f}, {-0.30f, 0.04f}, {-0.26f, 0.01f}, {-0.26f, -0.06f}, {-0.30f, -0.10f}, {-0.36f, -0.10f}, {-0.40f, -0.05f}, {-0.40f, 0.005f}},	// Left Eye 13
		{{-0.364f, 0.028f}, {-0.335f, 0.028f}, {-0.320f, 0.015f}, {-0.320f, -0.016f}, {-0.335f, -0.030f}, {-0.364f, -0.030f}, {-0.378f, -0.015f}, {-0.378f, 0.012f}, {-0.364f, 0.028f}},	// Left Pupil 14
		{{0.11f, 0.005f}, {0.15f, 0.04f}, {0.21f, 0.04f}, {0.25f, 0.01f}, {0.25f, -0.06f}, {0.21f, -0.10f}, {0.15f, -0.10f}, {0.11f, -0.05f}, {0.11f, 0.005f}},			// Right Eye 15
		{{0.146f, 0.028f}, {0.175f, 0.028f}, {0.190f, 0.015f}, {0.190f, -0.016f}, {0.175f, -0.030f}, {0.146f, -0.030f}, {0.132f, -0.015f}, {0.132f, 0.012f}, {0.146f, 0.028f}},		// Right Pupil 16
		{{-0.14f, -0.16f}, {-0.13f, -0.14f}, {-0.08f, -0.14f}, {-0.03f, -0.15f}, {-0.05f, -0.18f}, {-0.10f, -0.18f}, {-0.14f, -0.16f}},		// Nose 17
		{{-0.18f, -0.32f}, {-0.09f, -0.29f}, {-0.004f, -0.29f}, {0.05f, -0.33f}, {0.07f, -0.42f}, {0.009f, -0.47f}, {-0.09f, -0.47f}, {-0.15f, -0.41f}, {-0.18f, -0.32f}}		// Mouth 18
	};
	
	GLuint vao[18];
	GLuint positionsVBO[18];

	GLuint vao2[18];
	GLuint positionsVBO2[18];

	int currentSegment;
	std::vector<std::vector<std::vector<cgmath::vec2>>> segments;
	std::vector<std::vector<cgmath::vec2>> pointedSegments;
	float const CONSTANTSPACE = 0.01f;
	bool pointed = false;
	bool normal = false;

	void initializeSegment(std::vector<std::vector<cgmath::vec2>>& s);
	void initializePointedSegment();
	std::vector<cgmath::vec2> chaikin(std::vector<cgmath::vec2>& v);
	void drawSegment(std::vector<std::vector<cgmath::vec2>>& s);
	void drawPointedSegment();
	void pointedLineSegment();
	
};
