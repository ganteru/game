#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

/*
	Ein Zeichen wird durch ein Bild,
	eine Groesse, einen Abstand zu anderen Zeichen
	und durch den Abstand der vorherigen Zeichen
	festgelegt.
*/

struct Character
{
	GLuint			id;
	glm::ivec2		size;
	glm::ivec2		offset;
	unsigned int	advance;
};

class Text
{
private:
	GLuint						m_arr;
	GLuint						m_buff;
	FT_Library					m_lib;
	FT_Face						m_face;

	//  Die map enthält 128 Zeichen die geladen werden.
	std::map<GLchar, Character> m_chars;

	// Anzahl der zu ladenen Zeichen
	static const int			s_charset	= 128;

	// Anzahl der Eckpunkte und der Variablen
	static const int			s_vertices	= 6;
	static const int			s_floats	= 4;

public:
	Text(const std::string& font, int size);
	void draw(const std::string& text, float x, float y);
};