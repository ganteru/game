#pragma once
#include <glad/glad.h>
#include <vector>
#include "trail.h"

class Batch
{
private:
	GLuint m_arr;
	GLuint m_buff;

	const int m_vertices = 6;
	const int m_floats = 5;
	const int m_quads = 4000;

public:
	Batch();
	void batchData(std::vector<Trail*>& trails) const;
	void batchDraw() const;
};