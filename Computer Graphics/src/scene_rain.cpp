#include "scene_rain.h"

#include "ifile.h"
#include "t.h"
#include <IL/il.h>

#include <iostream>
#include <algorithm>

scene_rain::~scene_rain()
{
	// Borramos la memoria del ejecutable cuando
	// la escena deja de existir.
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &roomTexture);
}

void scene_rain::init()
{
	perspective = perspectiveMatrix(400.0f, 400.0f);
	ortographic = ortographicMatrix();
	view = viewMatrix();
	depthView = depthViewMatrix();

	particlesShader.create();
	particlesShader.attachShader("shaders/rain.vert", GL_VERTEX_SHADER);
	particlesShader.attachShader("shaders/rain.frag", GL_FRAGMENT_SHADER);
	particlesShader.setAttribute(0, "VertexPosition");
	particlesShader.setAttribute(1, "TexturePosition");
	particlesShader.setAttribute(2, "NormalPosition");
	particlesShader.link();

	particlesShader.activate();
	particlesShader.setUniformi("colorTexture", 0);
	particlesShader.setUniformi("depthTexture", 1);
	particlesShader.setUniformf("lightPosition", 0.0f, 35.0f, 0.0f);
	particlesShader.setUniformf("lightColor", 1.0f, 1.0f, 1.0f);
	particlesShader.deactivate();

	depthShader.create();
	depthShader.attachShader("shaders/depth.vert", GL_VERTEX_SHADER);
	depthShader.attachShader("shaders/depth.frag", GL_FRAGMENT_SHADER);
	depthShader.setAttribute(0, "VertexPosition");
	depthShader.setAttribute(1, "TexturePosition");
	depthShader.link();

	srand(static_cast <unsigned> (time(0)));

	initializePool();
	initializeBuffers();			
	
	ILuint image1, image2;
	ilGenImages(1, &image1);
	ilBindImage(image1);
	ilLoadImage("images/rain.png");

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

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
}

void scene_rain::awake()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void scene_rain::sleep()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void scene_rain::mainLoop() {

	if (activeParticles <= emissionRate) {
		activeParticles += t::delta_time().count() * emissionRate;   //Calcula el flujo de particulas con respecto al tiempo y razón de emisión.
	}

	if (activeParticles >= 1) { // Si es mayor o igual a uno, ya puede dibujar la particula
		for (int i = numberOfParticles - 1; i >= 0; i--) { //Por cada particula en el pool busca alguna que este apagada
			if (activeParticles < 1) {
				break;
			}
			else {
				if (!isActive[i]) {
					activateParticle(i);  //Si encuentras una apagada, préndela (al prenderse se van al inicio del arreglo, entonces estan en orden)
					totalAliveParticles += 1;  //Llevamos un contador de cuantas particulas existen, para que el sorteo y update de particulas lo haga SOLO con las que estan vivas, no con todas las particulas (mas eficiente)
				}
			}
		}
	}
	updateParticles();
	sortParticles();

	firstRender();
	secondRender();
}

void scene_rain::firstRender() {
	buffer.bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	depthShader.activate();
	glBindVertexArray(vaoroom);  //Render del cuarto

	model = 1.0f;
	mvp = perspective * depthView * model;
	depthShader.setUniformMatrix("mvpMatrix", mvp);

	glDrawElements(GL_TRIANGLES, indexesRoom.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

	glBindVertexArray(vao); //Render de las gotas

	int index = 0;
	model = (1.0f);
	model = rotateParticleMatrix(model);

	for (int i = 0; i < totalAliveParticles; i++) {  //Solo dibuja las particulas activas
		index = std::get<0>(magnitudes[i]);
		model[3][0] = pos[index].x;
		model[3][1] = pos[index].y;
		model[3][2] = pos[index].z;

		cgmath::mat4 mv = depthView * model;
		mv[0][0] = 1.0f; mv[2][0] = 0.0f;
		mv[0][1] = 0.0f; mv[2][1] = 0.0f;
		mv[0][2] = 0.0f; mv[2][2] = 1.0f;
		mvp = perspective * mv;
		depthShader.setUniformMatrix("mvpMatrix", mvp);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
	}

	glBindVertexArray(0);
	buffer.unbind();
}


void scene_rain::secondRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	particlesShader.activate();
	
	glBindVertexArray(vaoroom);  //Render del cuarto

	view = viewMatrix();
	particlesShader.setUniformf("cameraPosition", camPosition);

	cgmath::mat4 model = 1.0f;
	particlesShader.setUniformMatrix("modelMatrix", model);

	cgmath::mat4 mvp = perspective * view * model;
	particlesShader.setUniformMatrix("mvpMatrix", mvp);

	cgmath::mat3 normal_matrix = cgmath::mat3::transpose(cgmath::mat3::inverse(cgmath::mat3(model[0], model[1], model[2])));
	particlesShader.setUniformMatrix("normalMatrix", normal_matrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, roomTexture);

	glDrawElements(GL_TRIANGLES, indexesRoom.size(), GL_UNSIGNED_INT, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	
	glBindVertexArray(vao); //Render de las gotas

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	
	glDisable(GL_DEPTH_TEST);

	int index = 0;
	model = (1.0f);
	model = rotateParticleMatrix(model);

	for (int i = 0; i < totalAliveParticles; i++) {  //Solo dibuja las particulas activas
		index = std::get<0>(magnitudes[i]);
		model[3][0] = pos[index].x;
		model[3][1] = pos[index].y;
		model[3][2] = pos[index].z;

		particlesShader.setUniformMatrix("modelMatrix", model);

		normal_matrix = cgmath::mat3::transpose(cgmath::mat3::inverse(cgmath::mat3(model[0], model[1], model[2])));
		particlesShader.setUniformMatrix("normalMatrix", normal_matrix);

		cgmath::mat4 mv = view * model;
		mv[0][0] = 1.0f; mv[2][0] = 0.0f;
		mv[0][1] = 0.0f; mv[2][1] = 0.0f;
		mv[0][2] = 0.0f; mv[2][2] = 1.0f;
		cgmath::mat4 mvp = perspective * mv;
		particlesShader.setUniformMatrix("mvpMatrix", mvp);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	particlesShader.deactivate();

	float t = t::delta_time().count();

	if (aPressed) camPosition-=right*(distTras * t);
	if (dPressed) camPosition+=right*(distTras * t);
	if (wPressed) camPosition-=fwd*(distTras * t);
	if (sPressed) camPosition+=fwd*(distTras * t);
	if (jPressed) rotY+=(distRot * t);
	if (lPressed) rotY-=(distRot * t);
	if (kPressed && rotX>0) rotX-=(distRot * t);
	if (iPressed && rotX<3) rotX+=(distRot * t);
}

void scene_rain::resize(int width, int height)
{
	perspective = perspectiveMatrix(width, height);

	glViewport(0, 0, width, height);
}

void scene_rain::normalKeysDown(unsigned char key)
{

	if (key == 'w') wPressed = true;
	if (key == 's') sPressed = true;
	if (key == 'a') aPressed = true;
	if (key == 'd') dPressed = true;
	if (key == 'j') jPressed = true;
	if (key == 'l') lPressed = true;
	if (key == 'k') kPressed = true;
	if (key == 'i') iPressed = true;
	if (key == 'e') {
		if (airX < 70.0f) {
			airX += 14.0f;
			rotZ += 0.2f;
		}
	}
	if (key == 'q') {
		if (airX > -70.0f) {
			airX -= 14.0f;
			rotZ -= 0.2f;
		}
	}
	if (key == 'o') {  //Agrega Partículas

		emissionRate += 50.0f;

	}
	if (key == 'u') {  //Quita Partículas
	
		if (emissionRate >= 50.0f) {
			emissionRate -= 50.0f;
		}
	}

}

void scene_rain::normalKeysUp(unsigned char key)
{

	if (key == 'w') wPressed = false;
	if (key == 's') sPressed = false;
	if (key == 'a') aPressed = false;
	if (key == 'd') dPressed = false;
	if (key == 'j') jPressed = false;
	if (key == 'l') lPressed = false;
	if (key == 'k') kPressed = false;
	if (key == 'i') iPressed = false;
}

cgmath::mat4 scene_rain::viewMatrix()
{
	fwd = { 0,0,1 };
	right = { 1,0,0 };
	cgmath::mat4 original = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, 1, 0, 0),
		cgmath::vec4(0, 0, 1, 0),
		cgmath::vec4(0, 0, 0, 1)
	);

	cgmath::mat4 camera = rotateCameraMatrix(original);
	fwd *= camera[2];
	right *= camera[0];
	camera[3][0] = camPosition.x;
	camera[3][2] = camPosition.z;

	return cgmath::mat4::inverse(camera);
}

cgmath::mat4 scene_rain::depthViewMatrix()
{
	cgmath::mat4 original = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, 1, 0, 0),
		cgmath::vec4(0, 0, 1, 0),
		cgmath::vec4(0, 35, 0, 1)
	);
	cgmath::mat4 camera = rotateDepthCameraMatrix(original);

	return cgmath::mat4::inverse(camera);
}

cgmath::mat4 scene_rain::rotateDepthCameraMatrix(cgmath::mat4 m)
{
	float PI = 3.14159f;

	cgmath::mat4 rotationX = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, cos(-PI / 4), sin(-PI / 4), 0),
		cgmath::vec4(0, -sin(-PI / 4), cos(-PI / 4), 0),
		cgmath::vec4(0, 0, 0, 1)
	);

	return m * rotationX;
}


cgmath::mat4 scene_rain::rotateCameraMatrix(cgmath::mat4 m)
{
	float PI = 3.14159f;

	cgmath::mat4 rotationX = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, cos(2 * PI / 12 * rotX), sin(2 * PI / 12 * rotX), 0),
		cgmath::vec4(0, -sin(2 * PI / 12 * rotX), cos(2 * PI / 12 * rotX), 0),
		cgmath::vec4(0, 0, 0, 1)
	);

	cgmath::mat4 rotationY = cgmath::mat4(
		cgmath::vec4(cos(2 * PI / 6 * rotY), 0, -sin(2 * PI / 6 * rotY), 0),
		cgmath::vec4(0, 1, 0, 0),
		cgmath::vec4(sin(2 * PI / 6 * rotY), 0, cos(2 * PI / 6 * rotY), 0),
		cgmath::vec4(0, 0, 0, 1)
	);

	return m * rotationY*rotationX;
}

cgmath::mat4 scene_rain::rotateParticleMatrix(cgmath::mat4 m)
{
	float PI = 3.14159f;

	cgmath::mat4 rotationZ = cgmath::mat4(
		cgmath::vec4(cos(2 * PI / 12 * rotZ), sin(2 * PI / 12 * rotZ), 0, 0),
		cgmath::vec4(-sin(2 * PI / 12 * rotZ), cos(2 * PI / 12 * rotZ), 0, 0),
		cgmath::vec4(0, 0, 1, 0),
		cgmath::vec4(0, 0, 0, 1)
	);
	return m * rotationZ;
}


cgmath::mat4 scene_rain::perspectiveMatrix(float width, float height)
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

cgmath::mat4 scene_rain::ortographicMatrix()
{
	int right = 1000;
	int left = -1000;
	int top = 1000;
	int bottom = -1000;
	int far = 1000;
	int near = -1000;
	cgmath::mat4 ortographic = cgmath::mat4(
		cgmath::vec4(2 / (right - left), 0, 0, 0),
		cgmath::vec4(0, 2 / (top - bottom), 0, 0),
		cgmath::vec4(0, 0, -2 / (far - near), 0),
		cgmath::vec4(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1)
	);
	return ortographic;
}

void scene_rain::initializeBuffers() {
	// Creacion y activacion del vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Creacion y configuracion del buffer del atributo de posicion
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * triangle.size(), triangle.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &textureCoordinatesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textureCoordinatesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * coordinates.size(), coordinates.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normalizedVertexesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalizedVertexesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * normalVectors.size(), normalVectors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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

float scene_rain::random()
{
	int min = -1;
	int max = 1;
	float r = (float)rand() / (float)RAND_MAX;
	float rndm = min + r * (max - min);
	return rndm;

}

void scene_rain::initializePool() //Solo inicializa el pool de particulas, las particulas se inicializan hasta que se activan (en el main loop)
{
	float initialMean = 2000.0f;
	float varianceParticles = 0.0f;
	numberOfParticles = static_cast<int>(initialMean + random()*varianceParticles);

	for (int i = 0; i < numberOfParticles; i++) {

		pos.push_back(cgmath::vec3(0.0f,0.0f,0.0f));
		vel.push_back(cgmath::vec3(0.0f, 0.0f, 0.0f));
		acel.push_back(cgmath::vec3(0.0f, 0.0f, 0.0f));
		ttl.push_back(0.0f);
		magnitudes.push_back(std::make_tuple(i,-1));
		isActive.push_back(false);
	}
}


cgmath::vec3 scene_rain::initializePosition()
{
	float initialPosX = camPosition.x;
	float initialPosY = 80.0f;
	float initialPosZ = camPosition.z;
	float variancePosX = 100.0f;
	float variancePosY = 40.0f;
	float variancePosZ = 50.0f;

	float randPosX = (initialPosX + random()*variancePosX);
	float randPosY = (initialPosY + random()*variancePosY);
	float randPosZ = (initialPosZ + random()*variancePosZ);

	cgmath::vec3 v(randPosX, randPosY, randPosZ);
	return v;
}

cgmath::vec3 scene_rain::initializeVelocities()
{
	float meanVel = 120.0f;
	float varianceVel = 15.0f;
	float meanXVel = 30.0f;
	float xVelocity = 0.0f;
	float variancexVel = 0.0f;

	if (airX != 0) {
		xVelocity = meanXVel + random()*variancexVel;
	}

	float yVelocity = -(meanVel + random()*varianceVel);
	cgmath::vec3 v(0.0f, yVelocity, 0.0f);
	return v;
}

cgmath::vec3 scene_rain::initializeAcceleration()
{
	float meanAccel = airX;
	float varianceAccel = 0.0f;
	float acceleration = airX;

	if (airX != 0) {
		acceleration = meanAccel + random()*varianceAccel;
	}

	cgmath::vec3 v(acceleration, -9.81f, 0.0f);
	return v;
}

float scene_rain::initializeTimeToLive()
{
	float meanTtl = 8.5f;
	float varianceTtl = 1.5f;

	float ttl = meanTtl + random()*varianceTtl;

	return ttl;
}

void scene_rain::activateParticle(int i)
{
	pos[i] = initializePosition();
	vel[i] = initializeVelocities();
	acel[i] = initializeAcceleration();
	ttl[i] = initializeTimeToLive();
	isActive[i] = true;
	std::swap(pos[i], pos[totalAliveParticles]);
	std::swap(vel[i], vel[totalAliveParticles]);
	std::swap(acel[i], acel[totalAliveParticles]);
	std::swap(ttl[i], ttl[totalAliveParticles]);
	std::swap(isActive[i], isActive[totalAliveParticles]);
	activeParticles -= 1.0f;

}

void scene_rain::killParticle(int i)
{
	isActive[i] = false;
	std::swap(pos[i], pos[totalAliveParticles-1]);
	std::swap(vel[i], vel[totalAliveParticles-1]);
	std::swap(acel[i], acel[totalAliveParticles-1]);
	std::swap(ttl[i], ttl[totalAliveParticles-1]);
	std::swap(isActive[i], isActive[totalAliveParticles-1]);
	totalAliveParticles -= 1;
}

void scene_rain::updateParticles()
{
	for (int i = 0; i < totalAliveParticles; i++) {  //Actualiza las particulas vivas
		if (ttl[i] > 0) {
			pos[i] = pos[i] + (vel[i])*(t::delta_time().count());
			vel[i] = vel[i] + (acel[i]) * (t::delta_time().count());
			ttl[i] -= t::delta_time().count();
		}
		else {  //Si su tiempo de vida es 0, apagala y retirala del contador de particulas vivas.
			killParticle(i);
		}
	}
}

bool sortbysec(const std::tuple<int, float>& a, const std::tuple<int, float>& b)
{
	return (std::get<1>(a) > std::get<1>(b));
}

void scene_rain::sortParticles()
{
	for (int i = 0; i < totalAliveParticles; i++) { //Solamente sortea las particulas vivas
		cgmath::vec3 vector = pos[i] - camPosition;
		std::get<1>(magnitudes[i]) = vector.magnitudeNoSqrt();
		std::get<0>(magnitudes[i]) = i;  //Se asignan un nuevo indice a cada particula, y sobre la magnitud sortea.
	}
	std::sort(magnitudes.begin(), magnitudes.begin()+totalAliveParticles, sortbysec);
}
