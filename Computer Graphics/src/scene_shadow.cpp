#include "scene_shadow.h"

#include "ifile.h"
#include "t.h"
#include <IL/il.h>

#include <iostream>
#include <vector>

scene_shadow::~scene_shadow()
{
	// Borramos la memoria del ejecutable cuando
	// la escena deja de existir.
	glDeleteTextures(1, &roomTexture);
	glDeleteTextures(1, &cubeTexture);
}

void scene_shadow::init()
{
	perspective = perspectiveMatrix(400.0f, 400.0f);
	ortographic = ortographicMatrix();
	view = viewMatrix();
	depthView = depthViewMatrix();

	initializeBuffers();

	cubeShader.create();
	cubeShader.attachShader("shaders/rain.vert", GL_VERTEX_SHADER);
	cubeShader.attachShader("shaders/rain.frag", GL_FRAGMENT_SHADER);
	cubeShader.setAttribute(0, "VertexPosition");
	cubeShader.setAttribute(1, "TexturePosition");
	cubeShader.setAttribute(2, "NormalPosition");
	cubeShader.link();

	cubeShader.activate();
	cubeShader.setUniformi("texture", 0);
	cubeShader.setUniformf("lightPosition", 0.0f, 15.0f, 0.0f);
	cubeShader.setUniformf("lightColor", 1.0f, 1.0f, 1.0f);
	cubeShader.setUniformf("cameraPosition", 0.0f, 0.0f, 0.0f);
	cubeShader.deactivate();

	ILuint image1, image2;
	ilGenImages(1, &image1);
	ilBindImage(image1);
	ilLoadImage("images/crate.png");

	glGenTextures(1, &cubeTexture);
	glBindTexture(GL_TEXTURE_2D, cubeTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT),
		0,
		ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_TYPE),
		ilGetData());

	ilBindImage(0);
	ilDeleteImages(1, &image1);

	glBindTexture(GL_TEXTURE_2D, 0);

	ilGenImages(1, &image2);
	ilBindImage(image2);
	ilLoadImage("images/roomTexture.jpg");

	glGenTextures(1, &roomTexture);
	glBindTexture(GL_TEXTURE_2D, roomTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT),
		0,
		ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_TYPE),
		ilGetData());

	ilBindImage(0);
	ilDeleteImages(1, &image2);

	glBindTexture(GL_TEXTURE_2D, 0);

	depthShader.create();
	depthShader.attachShader("shaders/depth.vert", GL_VERTEX_SHADER);
	depthShader.attachShader("shaders/depth.frag", GL_FRAGMENT_SHADER);
	depthShader.setAttribute(0, "VertexPosition");
	depthShader.link();
}

void scene_shadow::awake()
{
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void scene_shadow::sleep()
{
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void scene_shadow::mainLoop() {
	firstRender();
	//secondRender();
}

void scene_shadow::firstRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	depthShader.activate();

	glBindVertexArray(vaoCube);

	model = modelMatrix();

	mvp = perspective * view * model;
	depthShader.setUniformMatrix("mvpMatrix", mvp);

	glDrawElements(GL_TRIANGLES, indexesCube.size(), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);

	/*glBindVertexArray(vaoroom);

	model=cgmath::mat4(1.0f);
	mvp = perspective * view * model;
	depthShader.setUniformMatrix("mvpMatrix", mvp);

	glDrawElements(GL_TRIANGLES, indexesRoom.size(), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);*/
	depthShader.deactivate();
}

void scene_shadow::secondRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	cubeShader.activate();

	glBindVertexArray(vaoCube);

	cgmath::mat4 model = modelMatrix();
	cubeShader.setUniformMatrix("modelMatrix", model);

	mvp = perspective * view * model;
	cubeShader.setUniformMatrix("mvpMatrix", mvp);

	cgmath::mat3 normal_matrix = cgmath::mat3::transpose(cgmath::mat3::inverse(cgmath::mat3(model[0], model[1], model[2])));
	cubeShader.setUniformMatrix("normalMatrix", normal_matrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTexture);

	glDrawElements(GL_TRIANGLES, indexesCube.size(), GL_UNSIGNED_INT, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	glBindVertexArray(vaoroom);
	
	model = 1.0f;
	cubeShader.setUniformMatrix("modelMatrix", model);

	mvp = perspective * view * model;
	cubeShader.setUniformMatrix("mvpMatrix", mvp);

	normal_matrix = cgmath::mat3::transpose(cgmath::mat3::inverse(cgmath::mat3(model[0], model[1], model[2])));
	cubeShader.setUniformMatrix("normalMatrix", normal_matrix);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, roomTexture);

	glDrawElements(GL_TRIANGLES, indexesRoom.size(), GL_UNSIGNED_INT, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	cubeShader.deactivate();
}

void scene_shadow::resize(int width, int height)
{
	perspective = perspectiveMatrix(width, height);

	glViewport(0, 0, width, height);

}

cgmath::mat4 scene_shadow::modelMatrix()
{
	float PI = 3.14159f;

	cgmath::mat4 rotationX = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, cos(2 * PI / 12 * t::elapsed_time().count()), sin(2 * PI / 12 * t::elapsed_time().count()), 0),
		cgmath::vec4(0, -sin(2 * PI / 12 * t::elapsed_time().count()), cos(2 * PI / 12 * t::elapsed_time().count()), 0),
		cgmath::vec4(0, 0, 0, 1)
	);

	cgmath::mat4 rotationY = cgmath::mat4(
		cgmath::vec4(cos(2 * PI / 6 * t::elapsed_time().count()), 0, -sin(2 * PI / 6 * t::elapsed_time().count()), 0),
		cgmath::vec4(0, 1, 0, 0),
		cgmath::vec4(sin(2 * PI / 6 * t::elapsed_time().count()), 0, cos(2 * PI / 6 * t::elapsed_time().count()), 0),
		cgmath::vec4(0, 0, 0, 1)
	);

	cgmath::mat4 rotationZ = cgmath::mat4(
		cgmath::vec4(cos(2 * PI / 12 * t::elapsed_time().count()), sin(2 * PI / 12 * t::elapsed_time().count()), 0, 0),
		cgmath::vec4(-sin(2 * PI / 12 * t::elapsed_time().count()), cos(2 * PI / 12 * t::elapsed_time().count()), 0, 0),
		cgmath::vec4(0, 0, 1, 0),
		cgmath::vec4(0, 0, 0, 1)
	);

	return rotationX*rotationY*rotationZ;
}

cgmath::mat4 scene_shadow::viewMatrix()
{
	cgmath::mat4 camera = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, 1, 0, 0),
		cgmath::vec4(0, 0, 1, 0),
		cgmath::vec4(0, 0, 30, 1)
	);

	return cgmath::mat4::inverse(camera);
}

cgmath::mat4 scene_shadow::depthViewMatrix()
{
	cgmath::mat4 original = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, 1, 0, 0),
		cgmath::vec4(0, 0, 1, 0),
		cgmath::vec4(0, 0, 0, 1)
	);
	//cgmath::mat4 camera = rotateDepthCameraMatrix(original);

	return cgmath::mat4::inverse(original);
}

cgmath::mat4 scene_shadow::rotateDepthCameraMatrix(cgmath::mat4 m)
{
	float PI = 3.14159f;

	cgmath::mat4 rotationX = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, cos(PI/2), sin(PI/2), 0),
		cgmath::vec4(0, -sin(PI/2), cos(PI/2), 0),
		cgmath::vec4(0, 0, 0, 1)
	);

	return m * rotationX;
}

cgmath::mat4 scene_shadow::perspectiveMatrix(float width, float height)
{
	float PI = 3.14159f;
	cgmath::mat4 perspective = cgmath::mat4(
		cgmath::vec4(1 / ((width / height)*tan((PI / 3.0f) / 2.0f)), 0, 0, 0),
		cgmath::vec4(0, 1 / tan((PI / 3.0f) / 2.0f), 0, 0),
		cgmath::vec4(0, 0, -(1000.0f + 1.0f) / (1000.0f - 1.0f), -1),
		cgmath::vec4(0, 0, -2 * 1000 * 1 / (1000.0f - 1.0f), 0)
	);
	return perspective;
}

cgmath::mat4 scene_shadow::ortographicMatrix()
{
	int right = 120;
	int left = -120;
	int top = 120;
	int bottom = -120;
	int far = 120;
	int near = -120;
	cgmath::mat4 ortographic = cgmath::mat4(
		cgmath::vec4(2/(right-left), 0, 0, 0),
		cgmath::vec4(0, 2 / (top-bottom), 0, 0),
		cgmath::vec4(0, 0,-2/(far-near), 0),
		cgmath::vec4(-(right+left)/(right-left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1)
	);
	return ortographic;
}

void scene_shadow::initializeBuffers() {
	// Creacion y activacion del vao
	glGenVertexArrays(1, &vaoCube);
	glBindVertexArray(vaoCube);

	// Creacion y configuracion del buffer del atributo de posicion
	glGenBuffers(1, &cubePositionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cubePositionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec4) * cube.size(), cube.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &cubeTextureCoordinatesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeTextureCoordinatesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * cubeTextureCoordinates.size(), cubeTextureCoordinates.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &cubeNormalVectorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeNormalVectorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * cubeNormalVectors.size(), cubeNormalVectors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// A diferencia de los buffers de atributos, los buffers de indices deben permanecer activos. No hacemos unbind.
	glGenBuffers(1, &cubeIndexesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexesCube.size(), indexesCube.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	glGenVertexArrays(1, &vaoroom);
	glBindVertexArray(vaoroom);

	glGenBuffers(1, &roomPositionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, roomPositionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec4) * room.size(), room.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &roomTextureCoordinatesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, roomTextureCoordinatesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * roomTextureCoordinates.size(), roomTextureCoordinates.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &roomNormalVectorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, roomNormalVectorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * roomNormalVectors.size(), roomNormalVectors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &roomIndexesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, roomIndexesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexesRoom.size(), indexesRoom.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

}

