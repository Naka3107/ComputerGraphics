#pragma once

#include "scene.h"
#include <vector>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

// Escena de prueba para comenzar a trabajar con
// fragment shaders.
class scene_shadow : public scene
{
public:
	~scene_shadow();

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

	GLuint vaoCube;
	GLuint vaoroom;
	GLuint cubePositionsVBO;
	GLuint cubeTextureCoordinatesVBO;
	GLuint cubeNormalVectorsVBO;
	GLuint cubeIndexesBuffer;
	GLuint roomIndexesBuffer;
	GLuint roomTextureCoordinatesVBO;
	GLuint roomPositionsVBO;
	GLuint roomNormalVectorsVBO;

	GLuint cubeTexture, roomTexture;

	std::vector<cgmath::vec4> cube = {
		{-3,3,3,1}, {3,3,3,1}, {3,9,3,1}, {-3,9,3,1},
		{-3,9,3,1}, {3,9,3,1}, {3,9,-3,1}, {-3,9,-3,1},
		{-3,9,-3,1}, {3,9,-3,1}, {3,3,-3,1}, {-3,3,-3,1},
		{-3,3,-3,1}, {3,3,-3,1}, {3,3,3,1}, {-3,3,3,1},
		{3,3,3,1}, {3,3,-3,1}, {3,9,-3,1}, {3,9,3,1},
		{-3,3,-3,1}, {-3,3,3,1}, {-3,9,3,1}, {-3,9,-3,1}
	};

	std::vector<cgmath::vec2> cubeTextureCoordinates = {
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0},
		{0.0,0.0}, {1.0,0.0}, {1.0,1.0}, {0.0,1.0}
	};

	std::vector<cgmath::vec3> cubeNormalVectors = {
		{0,0,1}, {0,0,1}, {0,0,1}, {0,0,1},
		{0,1,0}, {0,1,0}, {0,1,0}, {0,1,0},
		{0,0,-1}, {0,0,-1}, {0,0,-1}, {0,0,-1},
		{0,-1,0}, {0,-1,0}, {0,-1,0}, {0,-1,0},
		{1,0,0}, {1,0,0}, {1,0,0}, {1,0,0},
		{-1,0,0}, {-1,0,0}, {-1,0,0}, {-1,0,0}
	};

	std::vector<unsigned int> indexesCube = { 0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11,12,13,14,12,14,15,16,17,18,16,18,19,20,21,22,20,22,23 };

	std::vector<cgmath::vec4> room = {
		{-50,-10,-50,1}, {50,-10,-50,1}, {50,-10,50,1}, {-50,-10,50,1},  //piso
		{-50,-10,-50,1}, {50,-10,-50,1}, {50,30,-50,1}, {-50,30,-50,1},  //pared frontal
		{-50,-10,50,1}, {-50,-10,-50,1}, {-50,30,-50,1}, {-50,30,50,1},  //pared izquierda
		{50,-10,-50,1}, {50,-10,50,1}, {50, 30,50,1}, {50,30,-50,1},    //pared derecha
		{50,-10,50,1}, {-50,-10,50,1}, {-50,30,50,1}, {50,30,50,1} };   //pared trasera

	std::vector<cgmath::vec2> roomTextureCoordinates = {
		{0.0,0.0}, {8.0,0.0}, {8.0,8.0}, {0.0,8.0},
		{0.0,0.0}, {8.0,0.0}, {8.0,8.0}, {0.0,8.0},
		{0.0,0.0}, {8.0,0.0}, {8.0,8.0}, {0.0,8.0},
		{0.0,0.0}, {8.0,0.0}, {8.0,8.0}, {0.0,8.0},
		{0.0,0.0}, {8.0,0.0}, {8.0,8.0}, {0.0,8.0}
	};

	std::vector<unsigned int> indexesRoom = { 0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11,12,13,14,12,14,15,16,17,18,16,18,19 };

	std::vector<cgmath::vec3> roomNormalVectors = {
		{0,1,0}, {0,1,0}, {0,1,0}, {0,1,0},
		{0,0,1}, {0,0,1}, {0,0,1}, {0,0,1},
		{1,0,0}, {1,0,0}, {1,0,0}, {1,0,0},
		{-1,0,0}, {-1,0,0}, {-1,0,0}, {-1,0,0},
		{0,0,-1}, {0,0,-1}, {0,0,-1}, {0,0,-1}
	};

	void initializeBuffers();

	cgmath::mat4 modelMatrix();
	cgmath::mat4 viewMatrix();
	cgmath::mat4 perspectiveMatrix(float width, float height);
	cgmath::mat4 mvp;
	cgmath::mat4 model;
	cgmath::mat4 view;
	cgmath::mat4 perspective;
};

