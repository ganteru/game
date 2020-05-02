#include "shape.hpp"

Shape::Shape(int x, int y, int w, int h, const glm::vec3& color)
	: m_x{ x }, m_y{ y }, m_w{ w }, m_h{ h }, m_color{ color }
{
}

const int& Shape::getX() const
{
	return m_x;
}

const int& Shape::getY() const
{
	return m_y;
}

const int& Shape::getW() const
{
	return m_w;
}

const int& Shape::getH() const
{
	return m_h;
}

const glm::vec3& Shape::getColor() const
{
	return m_color;
}
