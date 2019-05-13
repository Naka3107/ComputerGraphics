#pragma once

#include "scene.h"
#include "shader_program.h"
#include "depth_buffer.h"
#include <vector>
#include <tuple>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

// Escena de prueba para comenzar a trabajar con
// fragment shaders.
class scene_fire : public scene
{
public:
	~scene_fire();

	void init();
	void awake();
	void sleep();
	void reset() { }
	void mainLoop();
	void firstRender();
	void secondRender();
	void resize(int width, int height);
	void normalKeysUp(unsigned char key);
	void specialKeys(int key) { }
	void passiveMotion(int x, int y) { }
	void normalKeysDown(unsigned char key);

private:
	depth_buffer buffer;

	shader_program particlesShader;
	shader_program depthShader;

	GLuint vao;
	GLuint vaoroom;
	GLuint positionsVBO;
	GLuint colorsVBO;
	GLuint textureCoordinatesVBO;
	GLuint normalizedVertexesVBO;
	GLuint indexesBuffer;
	GLuint roomIndexesBuffer;
	GLuint roomTextureCoordinatesVBO;
	GLuint roomPositionsVBO;
	GLuint roomNormalVectorsVBO;

	bool wPressed;
	bool sPressed;
	bool aPressed;
	bool dPressed;
	bool iPressed;
	bool kPressed;
	bool jPressed;
	bool lPressed;

	float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f, distRot = 2.0f, distTras = 10.0f, airX = 0.0f, activeParticles = 0.0f, emissionRate = 1200.0f;
	int numberOfParticles;
	int totalAliveParticles = 0;

	float velX = 0.0;
	float PI = 3.14159f;

	GLuint texture1, roomTexture;

	std::vector<cgmath::vec3> triangle = { { -0.5f, -0.5f,0}, {0.5f, -0.5f,0},  {0.5f,0.5f,0}, {-0.5f,0.5f,0} };
	std::vector<cgmath::vec2> coordinates = { {0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0,1.0} };
	std::vector<cgmath::vec3> normalVectors = { {0,0,1}, {0,0,1}, {0,0,1}, {0,0,1} };
	std::vector<unsigned int> indexes = { 0,1,2,0,2,3 };

	std::vector<cgmath::vec4> room = {
		{-50,-10,50,1}, {50,-10,50,1}, {50,-10,-50,1}, {-50,-10,-50,1},  //piso
		{-50,-10,-50,1}, {50,-10,-50,1}, {50,30,-50,1}, {-50,30,-50,1},  //pared frontal
		{-50,-10,50,1}, {-50,-10,-50,1}, {-50,30,-50,1}, {-50,30,50,1},  //pared izquierda
		{50,-10,-50,1}, {50,-10,50,1}, {50, 30,50,1}, {50,30,-50,1},    //pared derecha
		{50,-10,50,1}, {-50,-10,50,1}, {-50,30,50,1}, {50,30,50,1},     //pared trasera
		{-200,90,-200,1}, {200,90,-200,1}, {200,90,200,1}, {-200,90,200,1},     //cielo
	};


	std::vector<cgmath::vec2> roomTextureCoordinates = {
		{0.0,0.5}, {0.5,0.5}, {0.5,1.0}, {0.0,1.0},// PISO
		{0.5,0.5}, {1.0,0.5}, {1.0,1.0}, {0.5,1.0},
		{0.5,0.5}, {1.0,0.5}, {1.0,1.0}, {0.5,1.0},
		{0.5,0.5}, {1.0,0.5}, {1.0,1.0}, {0.5,1.0},
		{0.5,0.5}, {1.0,0.5}, {1.0,1.0}, {0.5,1.0},
		{0.0,0.0}, {0.5,0.0}, {0.5,0.5}, {0.0,0.5}
	};

	std::vector<unsigned int> indexesRoom = { 0,1,2,0,2,3,4,5,6,4,6,7,8,9,10,8,10,11,12,13,14,12,14,15,16,17,18,16,18,19,20,21,22,20,22,23 };
	std::vector<cgmath::vec3> roomNormalVectors = {
		{0,1,0}, {0,1,0}, {0,1,0}, {0,1,0},
		{0,0,1}, {0,0,1}, {0,0,1}, {0,0,1},
		{1,0,0}, {1,0,0}, {1,0,0}, {1,0,0},
		{-1,0,0}, {-1,0,0}, {-1,0,0}, {-1,0,0},
		{0,0,-1}, {0,0,-1}, {0,0,-1}, {0,0,-1},
		{0,-1,0}, {0,-1,0}, {0,-1,0}, {0,-1,0}
	};

	std::vector<cgmath::vec3> pos;
	std::vector<cgmath::vec3> vel;
	std::vector<cgmath::vec3> acel;
	std::vector<float> ttl;
	std::vector<std::tuple<int, float>> magnitudes;
	std::vector<bool> isActive;
	cgmath::vec3 fwd{ 0,0,1 };
	cgmath::vec3 right{ 1,0,0 };
	cgmath::vec3 camPosition{ 0,0,20 };

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
	cgmath::mat4 model;
	cgmath::mat4 mvp;
	cgmath::mat4 perspective;
};