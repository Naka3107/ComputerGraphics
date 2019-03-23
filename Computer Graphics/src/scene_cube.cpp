#include "scene_cube.h"

#include "ifile.h"
#include "t.h"

#include <iostream>
#include <vector>

scene_cube::~scene_cube()
{
	// Borramos la memoria del ejecutable cuando
	// la escena deja de existir.
	glDeleteProgram(shader_program);
}

void scene_cube::init()
{
	perspective = perspectiveMatrix(400, 400);
	view = viewMatrix();
	// Indices de los vertices para dibujar 2 triangulos, formando un cuadrado a pantalla completa
	initializeVector();
	// ifile es parte del codigo que yo les doy
	// El codigo fuente se encuentra en el proyecto Util
	// Su unico proposito en la vida es leer archivos de texto
	ifile shader_file;
	// El metodo read recibe la ruta al archivo de texto a leer
	// Si encuentra el archivo, intenta leerlo. En este caso,
	// estamos intentando leer un archivo llamado grid,
	// dentro de una carpeta shaders.
	shader_file.read("shaders/cube.vert");
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
	shader_file.read("shaders/cube.frag");
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
	glUseProgram(0);

}

void scene_cube::awake()
{
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void scene_cube::sleep()
{
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void scene_cube::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	newCube = perspective*view*modelMatrix();
	glUseProgram(shader_program);
	glBindVertexArray(vao);
	GLuint mvpMatrix = glGetUniformLocation(shader_program, "mvpMatrix");
	glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE,
		reinterpret_cast<GLfloat*>(&newCube));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	glUseProgram(0);
}

void scene_cube::resize(int width, int height)
{
	perspective = perspectiveMatrix(width, height);

	glViewport(0, 0, width, height);

	glUseProgram(shader_program);
	GLuint resolution_location =
		glGetUniformLocation(shader_program, "iResolution");
	glUniform2f(resolution_location, width, height);
	glUseProgram(0);
}

cgmath::mat4 scene_cube::modelMatrix()
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

cgmath::mat4 scene_cube::viewMatrix()
{
	cgmath::mat4 camera = cgmath::mat4(
		cgmath::vec4(1, 0, 0, 0),
		cgmath::vec4(0, 1, 0, 0),
		cgmath::vec4(0, 0, 1, 0),
		cgmath::vec4(0, 0, 10, 1)
	);

	return cgmath::mat4::inverse(camera);
}

cgmath::mat4 scene_cube::perspectiveMatrix(int width, int height)
{
	float PI = 3.14159f;
	cgmath::mat4 perspective = cgmath::mat4(
		cgmath::vec4(1/((width/height)*tan((2*PI/6)/2)), 0, 0, 0),
		cgmath::vec4(0, 1/ tan((2 * PI / 6) / 2), 0, 0),
		cgmath::vec4(0, 0, -(1000+1)/(1000-1), -2*1000*1 / (1000 - 1)),
		cgmath::vec4(0, 0, -1, 0)
	);
	return perspective;
}

void scene_cube::initializeVector() {
	// Creacion y activacion del vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Creacion y configuracion del buffer del atributo de posicion
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec4) * cube.size(), cube.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec4) * colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// A diferencia de los buffers de atributos, los buffers de indices deben permanecer activos. No hacemos unbind.
	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

