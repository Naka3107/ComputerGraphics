#include "scene_vertex.h"

#include "ifile.h"

scene_vertex::~scene_vertex()
{
}

void scene_vertex::init()
{
	ifile shader_file;
	shader_file.read("shaders/grid.vert");
	std::string vertex_source = shader_file.get_contents();
	const GLchar* vertex_source_c = (const GLchar*)vertex_source.c_str();
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source_c, nullptr);
	glCompileShader(vertex_shader);

	shader_file.read("shaders/solid_color.frag");
	std::string fragment_source = shader_file.get_contents();
	const GLchar* fragment_source_c = (const GLchar*)fragment_source.c_str();
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source_c, nullptr);
	glCompileShader(fragment_shader);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
}

void scene_vertex::awake()
{
}

void scene_vertex::sleep()
{
}

void scene_vertex::mainLoop()
{
}

void scene_vertex::resize(int width, int height)
{
}
