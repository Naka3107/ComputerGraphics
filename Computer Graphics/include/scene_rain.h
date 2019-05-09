#pragma once

#include "scene.h"
#include <vector>
#include <tuple>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

// Escena de prueba para comenzar a trabajar con
// fragment shaders.
class scene_rain : public scene
{
public:
	~scene_rain();

	void init();
	void awake();
	void sleep();
	void reset() { }
	void mainLoop();
	void resize(int width, int height);
	void normalKeysUp(unsigned char key) { }
	void specialKeys(int key) { }
	void passiveMotion(int x, int y) { }
	void normalKeysDown(unsigned char key);

private:
	GLuint shader_program;

	GLuint vao;
	GLuint vaoroom;
	GLuint positionsVBO;
	GLuint colorsVBO;
	GLuint textureCoordinatesVBO;
	GLuint normalizedVertexesVBO;
	GLuint indicesBuffer;
	GLuint roomIndexesBuffer;
	GLuint roomTextureCoordinatesVBO;
	GLuint roomPositionsVBO;
	GLuint roomNormalVectorsVBO;

	float camX = 0.0f, camZ = 0.0f, distTras = 1.0f, rotX = 0.0f, rotY = 0.0f, distRot = 0.05f, airX = 0.0f, rotZ = 0.0f, activeParticles = 0.0f, emissionRate = 100.0f;

	int numberOfParticles;
	int totalAliveParticles = 0;

	GLuint texture1, roomTexture;

	std::vector<cgmath::vec3> triangle = { { -0.8f, -0.288f,0}, {0.8f, -0.288f,0},  {0.0f,0.8f,0.0f} };
	std::vector<cgmath::vec2> coordinates = { {0.0, 0.0}, {1.0, 0.0}, {0.5, 1.0} };
	std::vector<cgmath::vec3> normalVectors = {	{0,0,1}, {0,0,1}, {0,0,1} };

	std::vector<cgmath::vec4> room = {
		{-50,-10,-50,1}, {50,-10,-50,1}, {50,-10,50,1}, {-50,-10,50,1},  //piso
		{-50,-10,-50,1}, {50,-10,-50,1}, {50,30,-50,1}, {-50,30,-50,1},  //pared frontal
		{-50,-10,50,1}, {-50,-10,-50,1}, {-50,30,-50,1}, {-50,30,50,1},  //pared izquierda
		{50,-10,-50,1}, {50,-10,50,1}, {50, 30,50,1}, {50,30,-50,1},    //pared derecha
		{50,-10,50,1}, {-50,-10,50,1}, {-50,30,50,1}, {50,30,50,1} };   //pared trasera

	std::vector<cgmath::vec2> roomTextureCoordinates = {
		{0.0,0.5}, {0.5,0.5}, {0.5,1.0}, {1.0,0.0},
		{0.5,0.5}, {1.0,0.5}, {1.0,1.0}, {0.5,1.0},
		{0.5,0.5}, {1.0,0.5}, {1.0,1.0}, {0.5,1.0},
		{0.5,0.5}, {1.0,0.5}, {1.0,1.0}, {0.5,1.0},	
		{0.5,0.5}, {1.0,0.5}, {1.0,1.0}, {0.5,1.0},
	};

	std::vector<unsigned int> indexesRoom = { 0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11,12,13,14,12,14,15,16,17,18,16,18,19 };

	std::vector<cgmath::vec3> roomNormalVectors = {
		{0,1,0}, {0,1,0}, {0,1,0}, {0,1,0},
		{0,0,1}, {0,0,1}, {0,0,1}, {0,0,1},
		{1,0,0}, {1,0,0}, {1,0,0}, {1,0,0},
		{-1,0,0}, {-1,0,0}, {-1,0,0}, {-1,0,0},
		{0,0,-1}, {0,0,-1}, {0,0,-1}, {0,0,-1}
	};

	std::vector<cgmath::vec3> pos;
	std::vector<cgmath::vec3> vel;
	std::vector<cgmath::vec3> acel;
	std::vector<float> ttl;
	std::vector<std::tuple<int, float>> magnitudes;
	std::vector<bool> isActive;

	float random();

	void initializeBuffers();
	void initializePool();

	cgmath::vec3 initializePosition();
	cgmath::vec3 initializeVelocities();
	cgmath::vec3 initializeAcceleration();
	float initializeTimeToLive();

	void activateParticle(int i);
	void killParticle(int i);
	void updateParticles();
	void sortParticles();

	cgmath::mat4 modelMatrix();
	cgmath::mat4 viewMatrix();
	cgmath::mat4 rotateCameraMatrix(cgmath::mat4 m);
	cgmath::mat4 rotateParticleMatrix(cgmath::mat4 m);
	cgmath::mat4 perspectiveMatrix(float width, float height);
	cgmath::mat4 view;
	cgmath::mat4 perspective;
};