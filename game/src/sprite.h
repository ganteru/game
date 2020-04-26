#pragma once
#include <glad/glad.h>
#include <string>
#include "import/stb_image.h"

class Sprite
{
private:
	GLuint	m_arr;
	GLuint	m_tex;
	int		m_width;
	int		m_height;

public:
	Sprite(const std::string& path);
	void draw() const;
};