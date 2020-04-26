#pragma once
#include <glm/glm.hpp>

class Trail
{
private:
	int			m_x;
	int			m_y;
	int			m_w;
	int			m_h;
	glm::vec3	m_color;

public:
	Trail(const int& x, const int& y, const int& w, const int& h, const glm::vec3& color);
	int&		getX();
	void		setX(const int& x);
	int&		getY();
	void		setY(const int& y);
	int&		getW();
	void		setW(const int& w);
	int&		getH();
	void		setH(const int& h);
	glm::vec3&	getColor();
	void		setColor(const glm::vec3& color);
};