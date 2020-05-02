#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shape
{
private:
	int			m_x;
	int			m_y;
	int			m_w;
	int			m_h;
	glm::vec3	m_color;

public:
	Shape(int x, int y, int w, int h, const glm::vec3& color);

	// Getter für die Position und die Groesse und die Farbe
	// Setter sind nicht erforderlich, weil die Klasse nur zum Zeichnen dient
	const int&			getX() const;
	const int&			getY() const;
	const int&			getW() const;
	const int&			getH() const;
	const glm::vec3&	getColor() const;
};