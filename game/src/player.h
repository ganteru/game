#pragma once
#include <glm/glm.hpp>

enum class Dir
{
	LEFT, RIGHT, UP, DOWN
};

class Player
{
private:
	int			m_x;
	int			m_y;
	int			m_w;
	int			m_h;
	Dir			m_dir;
	glm::vec3	m_color;

public:
	Player(const int& x, const int&y, const int& w, const int& h, const Dir& dir, const glm::vec3& color);
	void		update(int width, int height, int speed);
	int&		getX();
	void		setX(const int& x);
	int&		getY();
	void		setY(const int& y);
	int&		getWidth();
	void		setWidth(const int& w);
	int&		getHeight();
	void		setHeight(const int& h);
	Dir&		getDir();
	void		setDir(const Dir& dir);
	glm::vec3&	getColor();
	void		setColor(const glm::vec3& color);
};