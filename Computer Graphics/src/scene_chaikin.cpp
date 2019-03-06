#include "scene_chaikin.h"

void scene_chaikin::init()
{
	segments.push_back(originalSegment);
	currentSegment = 0;
	pointedSegments.resize(originalSegment.size());
	pointedLineSegment();
	initializeSegment(segments[currentSegment]);
	initializePointedSegment();
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
	if (pointed) {
		drawPointedSegment();
	}
	if (normal) {
		drawSegment(segments[currentSegment]);
	}
}

void scene_chaikin::normalKeysDown(unsigned char key)
{
	if (key == '0') {
		int index = key - '0';
		initializeSegment(segments[index]);
		currentSegment = index;
	}
	if (key == '1') {
		int index = key - '0';
		std::vector<std::vector<cgmath::vec2>> newSegmentVector;
		for (int i = 0; i < segments[index-1].size(); i++) {
			newSegmentVector.push_back(chaikin(segments[index - 1][i]));
		}
		segments.push_back(newSegmentVector);
		initializeSegment(segments[index]);
		currentSegment = index;
	}

	if (key == '2') {
		int index = key - '0';
		std::vector<std::vector<cgmath::vec2>> newSegmentVector;
		for (int i = 0; i < segments[index - 1].size(); i++) {
			newSegmentVector.push_back(chaikin(segments[index - 1][i]));
		}
		segments.push_back(newSegmentVector);
		initializeSegment(segments[index]);
		currentSegment = index;
	}

	if (key == '3') {
		int index = key - '0';
		std::vector<std::vector<cgmath::vec2>> newSegmentVector;
		for (int i = 0; i < segments[index - 1].size(); i++) {
			newSegmentVector.push_back(chaikin(segments[index - 1][i]));
		}
		segments.push_back(newSegmentVector);
		initializeSegment(segments[index]);
		currentSegment = index;
	}

	if (key == '4') {
		int index = key - '0';
		std::vector<std::vector<cgmath::vec2>> newSegmentVector;
		for (int i = 0; i < segments[index - 1].size(); i++) {
			newSegmentVector.push_back(chaikin(segments[index - 1][i]));
		}
		segments.push_back(newSegmentVector);
		initializeSegment(segments[index]);
		currentSegment = index;
	}
	if (key == 'p') {
		pointed = !pointed;
	}
	if (key == 'o') {
		normal = !normal;
	}
}

void scene_chaikin::initializeSegment(std::vector<std::vector<cgmath::vec2>>& s)
{
	glGenVertexArrays(s.size(), vao);
	glGenBuffers(s.size(), positionsVBO);

	for (int i = 0; i < s.size(); i++) {

		glBindVertexArray(vao[i]);
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

void scene_chaikin::initializePointedSegment()
{
	glGenVertexArrays(pointedSegments.size(), vao2);
	glGenBuffers(pointedSegments.size(), positionsVBO2);

	for (int i = 0; i < pointedSegments.size(); i++) {

		glBindVertexArray(vao2[i]);
		glBindBuffer(GL_ARRAY_BUFFER, positionsVBO2[i]);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(cgmath::vec2) * pointedSegments[i].size(),
			pointedSegments[i].data(),
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

void scene_chaikin::drawPointedSegment()
{
	for (int i = 0; i < pointedSegments.size(); i++) {
		glBindVertexArray(vao2[i]);
		// Llamada a dibujar.
		// Tipo de primitiva.
		// Desde qué vértice va a empezar a dibujar.
		// Cuántos vértices se van a dibujar.
		glDrawArrays(GL_LINES, 0, pointedSegments[i].size());
		// Unbind del vao y todos los atributos.
		glBindVertexArray(0);
	}
}

void scene_chaikin::pointedLineSegment()
{
	for (int i = 0; i< originalSegment.size(); i++) {
		for (int j = 0; j+1 < originalSegment[i].size(); j++) {

			cgmath::vec2 vector = (originalSegment[i][j + 1] - originalSegment[i][j]);
			float magnitude = vector.magnitude();
			cgmath::vec2 normalizedVector = cgmath::vec2::normalize(vector);
			for (float p = CONSTANTSPACE; p < magnitude; p += CONSTANTSPACE) {
				pointedSegments[i].push_back(originalSegment[i][j] + normalizedVector * p);
			}
		}
	}
}


std::vector<cgmath::vec2> scene_chaikin::chaikin(std::vector<cgmath::vec2>& v)
{ 
	std::vector<cgmath::vec2> newVector;
	
	if (v.size() == 2) {
		return v;
	}
	
	else {

		if (v.front() == v.back()) {
			v.push_back(v[1]);
		}
		else {
			newVector.push_back(v.front());
		}

		for (int i = 0; i + 1 < v.size(); i++) {
			newVector.push_back(0.75f*v[i] + 0.25f*v[i + 1]);
			newVector.push_back(0.25f*v[i] + 0.75f*v[i + 1]);
		}

		if (v[1] == v.back()) {
			v.pop_back();
		}
		else {
			newVector.push_back(v.back());
		}

		return newVector;
	}
}


