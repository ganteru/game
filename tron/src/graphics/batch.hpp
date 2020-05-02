#pragma once
#include <glad/glad.h>
#include <vector>
#include "shape.hpp"

/*
	Die Klasse Batch ist speziell für die Spieler ausgelegt.

	Bei mehreren hunderten von Bildern die für den Spieler eine Spur
	ziehen, muss das Zeichenverfahren GL_DYNAMIC_DRAW von OpenGL verwendet werden.
*/
class Batch
{
private:
	GLuint m_arr;
	GLuint m_buff;

	const GLsizeiptr m_vertices = 6;
	const GLsizeiptr m_floats = 5;
	const GLsizeiptr m_quads = 6000;

public:
	Batch();
	void batchData(const std::vector<Shape*>& shapes) const;
	void drawBatch() const;
};