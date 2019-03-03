#include "scene_conchoid.h"

#include "vec2.h"

#include <vector>

// Se manda a llamar una vez nada más cuando inicia la aplicación.
void scene_conchoid::init()
{
	std::vector<cgmath::vec2> positions1;
	for (float t = -0.5593f; t < 0.55937f; t += 0.01f) {
		positions1.push_back(cgmath::vec2(t + (k1*t)/sqrt(b*b + t*t), b + (b*k1) / sqrt(b*b + t * t)));
	}
	sizeOfVector1 = positions1.size();

	std::vector<cgmath::vec2> positions2;
	for (float t = -1.4902f; t < 1.4902f; t += 0.01f) {
		positions2.push_back(cgmath::vec2(t + (k2*t) / sqrt(b*b + t * t), b + (b*k2) / sqrt(b*b + t * t)));
	}
	sizeOfVector2 = positions2.size();


	glGenVertexArrays(1, &vao1);
		
	glBindVertexArray(vao1);

	glGenBuffers(1, &positionsVBO1);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO1);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(cgmath::vec2) * sizeOfVector1,
		positions1.data(),
		GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);
	glGenBuffers(1, &positionsVBO2);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO2);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(cgmath::vec2) * sizeOfVector2,
		positions2.data(),
		GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void scene_conchoid::awake()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void scene_conchoid::sleep()
{
	glPointSize(1.0f);
}

void scene_conchoid::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind del vao que tiene todos los atributos.
	glBindVertexArray(vao1);
	// Llamada a dibujar.
	// Tipo de primitiva.
	// Desde qué vértice va a empezar a dibujar.
	// Cuántos vértices se van a dibujar.
	glDrawArrays(GL_LINE_STRIP, 0, sizeOfVector1);
	// Unbind del vao y todos los atributos.
	glBindVertexArray(0);

	glBindVertexArray(vao2);
	glDrawArrays(GL_LINE_STRIP, 0, sizeOfVector2);
	glBindVertexArray(0);
}
