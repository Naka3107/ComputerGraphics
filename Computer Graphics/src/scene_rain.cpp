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
	glDeleteProgram(shader_program);
}

void scene_rain::init()
{
	perspective = perspectiveMatrix(400.0f, 400.0f);
	view = viewMatrix();

	srand(static_cast <unsigned> (time(0)));

	initializePool();
	initializeBuffers();
	// ifile es parte del codigo que yo les doy
	// El codigo fuente se encuentra en el proyecto Util
	// Su unico proposito en la vida es leer archivos de texto
	ifile shader_file;
	// El metodo read recibe la ruta al archivo de texto a leer
	// Si encuentra el archivo, intenta leerlo. En este caso,
	// estamos intentando leer un archivo llamado grid,
	// dentro de una carpeta shaders.
	shader_file.read("shaders/rain.vert");
	// Obtenemos los contenidos leidos en el paso anterior
	// utilizando el metodo get_contents. Regresa un string
	std::string vertex_source = shader_file.get_contents();
	// OpenGL es un API de C, por lo que no trabaja con
	// strings de C++. Tenemos que hacer un cast a un tipo de
	// dato que OpenGL entienda. Podemos usar strings de C (char*)
	// o utilizar el tipo de dato definido por OpenGL (GLchar*).
	// Preferimos lo segundo.
	const GLchar* vertex_source_c = (const GLchar*)vertex_source.c_str();
	// Creamos el identificador para un vertex shader,
	// utiliznado la funcion glCreateShader. La funcion
	// regresa el identificador y lo guardamos en la variable
	// vertex_shader.
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	// Utilizando la funcion glShaderSource, indicamos que queremos
	// enviar el codigo fuente del shader. La funcion espera:
	// Identificador del shader (vertex_shader)
	// Cuantos codigos fuentes queremos manadar (1)
	// El código fuente (vertex_source_c)
	// La longitud del codigo fuente. Si usamos nullptr, se
	// asume que debe continuar leyendo hasta encontrar un nullptr.
	glShaderSource(vertex_shader, 1, &vertex_source_c, nullptr);
	// Compilamos el codigo fuente contenido en el shader
	// con identificador vertex_shader.
	glCompileShader(vertex_shader);

	// Revision de errores de compilacion del vertex shader
	GLint vertex_compiled;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_compiled);
	if (vertex_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(vertex_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in vertex shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}

	// Repetimos el mismo proceso, pero ahora para un
	// fragment shader contenido en un archivo llamado
	// solid_color.frag dentro de la carpeta shaders.
	shader_file.read("shaders/rain.frag");
	std::string fragment_source = shader_file.get_contents();
	const GLchar* fragment_source_c = (const GLchar*)fragment_source.c_str();
	// El identificador del shader lo creamos pero para un 
	// shader de tipo fragment.
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source_c, nullptr);
	glCompileShader(fragment_shader);

	// Revision de errores de compilacion del fragment shader
	GLint fragment_compiled;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_compiled);
	if (fragment_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(fragment_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in fragment shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}

	// Una vez que hemos creado los shaders necesarios,
	// creamos el manager utilizando la funcion glCreateProgram
	// que regresa el id.
	shader_program = glCreateProgram();
	// Utilizamos glAttachShader para asociar un shader con el manager
	// En este caso, shader_program es manager de vertex_shader
	glAttachShader(shader_program, vertex_shader);
	// En este caso, shader_program es manager de fragment_shader
	glAttachShader(shader_program, fragment_shader);
	glBindAttribLocation(shader_program, 0, "VertexPosition");
	glBindAttribLocation(shader_program, 1, "TexturePosition");
	glBindAttribLocation(shader_program, 2, "NormalPosition");
	// Ejecutamos el proceso de linkeo. En esta etapa se busca
	// que los shaders puedan trabajar en conjunto y todo este
	// definido correctamente.
	glLinkProgram(shader_program);

	// Tambien deberiamos verificar que el proceso de linkeo
	// termine sin errores. Por tiempo, asumimos que el
	// resultado fue correcto.

	// Borramos los shaders, porque ya tenemos el ejecutable
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	// Enviamos la resolucion de la ventana al inicio de la
	// aplicacion. La variable es un uniform vec2.
	// Tenemos que obtener la posicion de esa variable en el shader
	// y asignarle un valor utilizando glUniform2f
	glUseProgram(shader_program);
	GLuint resolution_location = glGetUniformLocation(shader_program,
		"iResolution");
	glUniform2f(resolution_location, 400.0f, 400.0f);

	// Inicializar DevIL. Esto se debe hacer sólo una vez en
	// todo el ciclo de vida del programa.
	ilInit();
	// Cambiar el punto de origen de las texturas. Por default, DevIL
	// pone un punto de origen en la esquina superior izquierda.
	// Eso es compatible con el sistema operativo, pero no con el
	// funcionamiento de OpenGL.
	ilEnable(IL_ORIGIN_SET);
	// Configurar el punto de origen de las texturas en la esquina
	// inferior izquierda
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
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
	ilLoadImage("images/room.jpg");

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

	GLuint textureLocation = glGetUniformLocation(shader_program, "texture");
	glUniform1i(textureLocation, 0);

	GLuint light_position = glGetUniformLocation(shader_program, "lightPosition");
	glUniform3f(light_position, 5.0f, 10.0f, 10.0f);

	GLuint light_color = glGetUniformLocation(shader_program, "lightColor");
	glUniform3f(light_color, 1.0f, 1.0f, 1.0f);

	glUseProgram(0);
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

void scene_rain::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(shader_program);
	glBindVertexArray(vaoroom);  //Render del cuarto

	GLuint modelMatrix = glGetUniformLocation(shader_program, "modelMatrix");
	GLuint normalMatrix = glGetUniformLocation(shader_program, "normalMatrix");
	GLuint mvpMatrix = glGetUniformLocation(shader_program, "mvpMatrix");

	cgmath::mat4 model = 1.0f;
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, reinterpret_cast<GLfloat*>(&model));

	cgmath::mat4 mvp = perspective * view * model;
	glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE,
		reinterpret_cast<GLfloat*>(&mvp));

	cgmath::mat3 normal_matrix = cgmath::mat3::transpose(cgmath::mat3::inverse(cgmath::mat3(model[0], model[1], model[2])));
	glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, reinterpret_cast<GLfloat*>(&normal_matrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, roomTexture);

	glDrawElements(GL_TRIANGLES, indexesRoom.size(), GL_UNSIGNED_INT, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);


	glBindVertexArray(vao); //Render de las gotas

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	view = viewMatrix();

	if (activeParticles <= emissionRate) {
		activeParticles += t::delta_time().count() * emissionRate;   //Calcula el flujo de particulas con respecto al tiempo y razón de emisión.
	}

	if (activeParticles >= 1) { // Si es mayor o igual a uno, ya puede dibujar la particula
		for (int i = numberOfParticles-1; i >= 0 ; i--) { //Por cada particula en el pool busca alguna que este apagada
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

	int index = 0;
	model = (1.0f);
	model = rotateParticleMatrix(model);

	for (int i = 0; i < totalAliveParticles; i++) {  //Solo dibuja las particulas activas
		index = std::get<0>(magnitudes[i]);
		model[3][0] = pos[index].x;
		model[3][1] = pos[index].y;
		model[3][2] = pos[index].z;

		glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, reinterpret_cast<GLfloat*>(&model));

		cgmath::mat3 normal_matrix = cgmath::mat3::transpose(cgmath::mat3::inverse(cgmath::mat3(model[0], model[1], model[2])));
		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, reinterpret_cast<GLfloat*>(&normal_matrix));

		cgmath::mat4 mv = view * model;
		mv[0][0] = 1.0f; mv[2][0] = 0.0f;
		mv[0][1] = 0.0f; mv[2][1] = 0.0f;
		mv[0][2] = 0.0f; mv[2][2] = 1.0f;
		cgmath::mat4 mvp = perspective * mv;
		glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE,
			reinterpret_cast<GLfloat*>(&mvp));
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	glUseProgram(0);
}

void scene_rain::resize(int width, int height)
{
	perspective = perspectiveMatrix(width, height);

	glViewport(0, 0, width, height);

	glUseProgram(shader_program);
	GLuint resolution_location =
		glGetUniformLocation(shader_program, "iResolution");
	glUniform2f(resolution_location, width, height);
	glUseProgram(0);
}

void scene_rain::normalKeysDown(unsigned char key)
{

	if (key == 'w') {
		camZ -= distTras;
	}
	if (key == 's') {
		camZ += distTras;
	}
	if (key == 'a') {
		camX -= distTras;
	}
	if (key == 'd') {
		camX += distTras;
	}
	if (key == 'j') {
		rotY += distRot;
	}
	if (key == 'l') {
		rotY -= distRot;
	}
	if (key == 'k') {
		if (rotX > 0) {
			rotX -= distRot;
		}
	}
	if (key == 'i') {
		if (rotX < 3) {
			rotX += distRot;
		}
	}
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
		//int add = 100;
		//for (int i = 0; i < add; i++) {
		//	pos.push_back(initializePosition());
		//	acel.push_back(initializeAcceleration());
		//	vel.push_back(initializeVelocities());
		//	ttl.push_back(float(t::elapsed_time().count()));
		//	magnitudes.push_back(std::make_tuple(numberOfParticles+i, 0));
		//}
		//numberOfParticles += add;

		emissionRate += 50.0f;

	}
	if (key == 'u') {  //Quita Partículas
		/*int sub = 100;
		if (numberOfParticles > 100) {
			magnitudes.clear();
			for (int i = 0; i < sub; i++) {
				pos.pop_back();
				acel.pop_back();
				vel.pop_back();
				ttl.pop_back();
			}
			numberOfParticles -= sub;
			for (int i = 0; i < numberOfParticles; i++) {
				magnitudes.push_back(std::make_tuple(i, 0));
			}
		}*/
		if (emissionRate >= 50.0f) {
			emissionRate -= 50.0f;
		}
	}

}

cgmath::mat4 scene_rain::viewMatrix()
{
	cgmath::mat4 original = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, 1, 0, 0),
		cgmath::vec4(0, 0, 1, 0),
		cgmath::vec4(0, 0, 0, 1)
	);

	cgmath::mat4 camera = rotateCameraMatrix(original);
	camera[3][0] += camX;
	camera[3][2] += camZ;

	GLuint camera_position = glGetUniformLocation(shader_program, "cameraPosition");
	glUniform3f(camera_position, camX, 0.0f, camZ);

	return cgmath::mat4::inverse(camera);
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
	float initialPosX = camX;
	float initialPosY = 80.0f;
	float initialPosZ = camZ;
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
	//if (i > 0 && i < pos.size()) { //Si la particula ya existe, borrala.
	//	pos.erase(pos.begin() + i);
	//	vel.erase(vel.begin() + i);
	//	acel.erase(acel.begin() + i);
	//	ttl.erase(ttl.begin() + i);
	//	magnitudes.erase(magnitudes.begin() + i);
	//}
	//isActive.erase(isActive.begin() + i); //Borra esa referencia del pool
	//pos.insert(pos.begin(), initializePosition());
	//vel.insert(vel.begin(), initializeVelocities());
	//acel.insert(acel.begin(), initializeAcceleration());
	//ttl.insert(ttl.begin(), initializeTimeToLive());
	//magnitudes.insert(magnitudes.begin(), std::make_tuple(i, 0));
	//isActive.insert(isActive.begin(), true); //Inicializa la particula y activala (insertas los datos al principio del arreglo, no al final).
	//activeParticles -= 1.0f;

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
	//pos.erase(pos.begin() + i);
	//vel.erase(vel.begin() + i);
	//acel.erase(acel.begin() + i);
	//ttl.erase(ttl.begin() + i);
	//magnitudes.erase(magnitudes.begin() + i);
	//isActive.erase(isActive.begin() + i);
	//pos.push_back(cgmath::vec3(0.0f, 0.0f, 0.0f));
	//vel.push_back(cgmath::vec3(0.0f, 0.0f, 0.0f));
	//acel.push_back(cgmath::vec3(0.0f, 0.0f, 0.0f));
	//ttl.push_back(0.0f);
	//magnitudes.push_back(std::make_tuple(0, 0));
	//isActive.push_back(false);

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
	cgmath::vec3 cameraPosition = { camX, 0, camZ };

	for (int i = 0; i < totalAliveParticles; i++) { //Solamente sortea las particulas vivas
		cgmath::vec3 vector = pos[i] - cameraPosition;
		std::get<1>(magnitudes[i]) = vector.magnitudeNoSqrt();
		std::get<0>(magnitudes[i]) = i;  //Se asignan un nuevo indice a cada particula, y sobre la magnitud sortea.
	}
	std::sort(magnitudes.begin(), magnitudes.end(), sortbysec);
}
