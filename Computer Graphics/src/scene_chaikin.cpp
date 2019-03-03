#include "scene_chaikin.h"

void scene_chaikin::init()
{
	initializeSegment(segments);
	currentSegment = segments;
}

void scene_chaikin::awake()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void scene_chaikin::sleep()
{
	glPointSize(1.0f);
}

void scene_chaikin::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawSegment(currentSegment);
}

void scene_chaikin::normalKeysDown(unsigned char key)
{
	if (key == '0') {
		initializeSegment(segments);
		currentSegment = segments;
	}
	if (key == '1') {
		std::vector<std::vector<cgmath::vec2>> newSegmentVector;
		for (int i = 0; i < segments.size(); i++) {
			newSegmentVector.push_back(chaikin(segments[i]));
		}
		initializeSegment(newSegmentVector);
		currentSegment = newSegmentVector;
	}

	if (key == '2') {
		
	}
}

void scene_chaikin::initializeSegment(std::vector<std::vector<cgmath::vec2>>& s)
{
	for (int i = 0; i < s.size(); i++) {
		glGenVertexArrays(s.size(), &vao[i]);

		glBindVertexArray(vao[i]);

		glGenBuffers(s.size(), &positionsVBO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, positionsVBO[i]);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(cgmath::vec2) * s[i].size(),
			s[i].data(),
			GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
}

void scene_chaikin::drawSegment(std::vector<std::vector<cgmath::vec2>>& s)
{
	for (int i = 0; i < s.size(); i++) {
		glBindVertexArray(vao[i]);
		// Llamada a dibujar.
		// Tipo de primitiva.
		// Desde qué vértice va a empezar a dibujar.
		// Cuántos vértices se van a dibujar.
		glDrawArrays(GL_LINE_STRIP, 0, s[i].size() );
		// Unbind del vao y todos los atributos.
		glBindVertexArray(0);
	}
}


std::vector<cgmath::vec2> scene_chaikin::chaikin(std::vector<cgmath::vec2>& v)
{ 
	std::vector<cgmath::vec2> newVector;
	
	if (v.front() == v.back()) {
		v.push_back(v[1]);
	}
	else {
		newVector.push_back(v.front());
	}

	for (int i = 0; i+1 < v.size(); i++) {
		newVector.push_back(0.75f*v[i] + 0.25f*v[i+1]);
		newVector.push_back(0.25f*v[i] + 0.75f*v[i+1]);
	}
	
	if (v[1] == v.back()) {
		v.pop_back();
	}
	else {
		newVector.push_back(v.back());
	}

	return newVector;
}


