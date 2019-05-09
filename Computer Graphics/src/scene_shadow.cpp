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
	glDeleteProgram(shader_program);
}

void scene_shadow::init()
{
	perspective = perspectiveMatrix(400.0f, 400.0f);
	view = viewMatrix();

	initializeBuffers();
	// ifile es parte del codigo que yo les doy
	// El codigo fuente se encuentra en el proyecto Util
	// Su unico proposito en la vida es leer archivos de texto
	ifile shader_file;
	// El metodo read recibe la ruta al archivo de texto a leer
	// Si encuentra el archivo, intenta leerlo. En este caso,
	// estamos intentando leer un archivo llamado grid,
	// dentro de una carpeta shaders.
	shader_file.read("shaders/shadow.vert");
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
	shader_file.read("shaders/shadow.frag");
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
	ilLoadImage("images/wall.png");

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

	GLuint camera_position = glGetUniformLocation(shader_program, "cameraPosition");
	glUniform3f(camera_position, 0.0f, 0.0f, 0.0f);

	glUseProgram(0);
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

void scene_shadow::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_program);
	glBindVertexArray(vaoCube);

	cgmath::mat4 model = modelMatrix();

	GLuint modelMatrix = glGetUniformLocation(shader_program, "modelMatrix");
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, reinterpret_cast<GLfloat*>(&model));

	mvp = perspective * view* model;

	GLuint mvpMatrix = glGetUniformLocation(shader_program, "mvpMatrix");
	glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE,
		reinterpret_cast<GLfloat*>(&mvp));

	GLuint normalMatrix = glGetUniformLocation(shader_program, "normalMatrix");

	cgmath::mat3 normal_matrix = cgmath::mat3::transpose(cgmath::mat3::inverse(cgmath::mat3(model[0], model[1], model[2])));
	glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, reinterpret_cast<GLfloat*>(&normal_matrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTexture);

	glDrawElements(GL_TRIANGLES, indexesCube.size(), GL_UNSIGNED_INT, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	glBindVertexArray(vaoroom);
	
	model=1.0f;
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, reinterpret_cast<GLfloat*>(&model));

	mvp = perspective * view * model;
	glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE,
		reinterpret_cast<GLfloat*>(&mvp));

	normal_matrix = cgmath::mat3::transpose(cgmath::mat3::inverse(cgmath::mat3(model[0], model[1], model[2])));
	glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, reinterpret_cast<GLfloat*>(&normal_matrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, roomTexture);

	glDrawElements(GL_TRIANGLES, indexesRoom.size(), GL_UNSIGNED_INT, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void scene_shadow::resize(int width, int height)
{
	perspective = perspectiveMatrix(width, height);

	glViewport(0, 0, width, height);

	glUseProgram(shader_program);
	GLuint resolution_location =
		glGetUniformLocation(shader_program, "iResolution");
	glUniform2f(resolution_location, width, height);
	glUseProgram(0);
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
		cgmath::vec4(0, 0, 50, 1)
	);

	return cgmath::mat4::inverse(camera);
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

