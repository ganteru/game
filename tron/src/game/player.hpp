#pragma once
#include <glm/glm.hpp>
#include "input.hpp"


/*
	Der Player wird durch eine Richtung, Position und Farbe dargestellt.
	Die Richtung entscheidet in der Update-Methode, wie sich die Position verändern soll.
	Die Farbe wird dazu benötigt, dass die Spuren des Players mit der jeweils passenden
	Farbe gezeichnet werden.
*/

enum class Dir
{
	LEFT, RIGHT, UP, DOWN
};

class Player
{
private:
	int			m_x;
	int			m_y;
	Dir			m_dir;
	glm::vec3	m_color;

public:
	Player(int x, int y, Dir dir, const glm::vec3& color);
	void		movement(const Input& input);
	void		update(int x, int y, int w, int h, int s);
	int&		getX();
	void		setX(int x);
	int&		getY();
	void		setY(int y);
	Dir&		getDir();
	void		setDir(Dir dir);
	glm::vec3&	getColor();
};