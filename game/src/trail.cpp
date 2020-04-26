#include "trail.h"

Trail::Trail(const int& x, const int& y, const int& w, const int& h, const glm::vec3& color)
	: m_x{ x }, m_y{ y }, m_w{ w }, m_h{ h }, m_color{ color }
{
}

int& Trail::getX()
{
	return m_x;
}

void Trail::setX(const int& x)
{
	m_x = x;
}

int& Trail::getY()
{
	return m_y;
}

void Trail::setY(const int& y)
{
	m_y = y;
}

int& Trail::getW()
{
	return m_w;
}

void Trail::setW(const int& w)
{
	m_w = w;
}

int& Trail::getH()
{
	return m_h;
}

void Trail::setH(const int& h)
{
	m_h = h;
}

glm::vec3& Trail::getColor()
{
	return m_color;
}

void Trail::setColor(const glm::vec3& color)
{
	m_color = color;
}
