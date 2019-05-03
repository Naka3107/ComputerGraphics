#pragma once

#include "scene.h"
#include <vector>
#include <tuple>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
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
	GLuint positionsVBO;
	GLuint colorsVBO;
	GLuint textureCoordinatesVBO;
	GLuint indicesBuffer;

	float camX = 0.0f, camZ = 0.0f, distTras = 1.0f, rotX=0.0f, rotY=0.0f, distRot=0.1f, airX=0.0f, rotZ=0.0f;
	int numberOfParticles;

	GLuint texture1;
	std::vector<cgmath::vec3> triangle = {{ -0.8f, -0.288f,0}, {0.8, -0.288f,0},  {0.0f,0.6f,0.0f} };
	std::vector<cgmath::vec2> coordinates = { {0.0, 0.0}, {1.0, 0.0}, {0.5, 1.0} };


	std::vector<cgmath::vec3> pos;
	std::vector<cgmath::vec3> vel;
	std::vector<cgmath::vec3> acel;
	std::vector<float> ttl;
	std::vector<std::tuple<int, float>> magnitudes;

	/*std::vector<float> magnitudes;
	std::vector<int>indices;*/

	float random();

	void initializeVector();

	void initializeParticles();

	cgmath::vec3 initializePosition();
	cgmath::vec3 initializeVelocities();
	cgmath::vec3 initializeAcceleration();

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