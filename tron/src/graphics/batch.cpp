#include "batch.hpp"

Batch::Batch()
{
	glGenVertexArrays(1, &m_arr);
	glGenBuffers(1, &m_buff);

	// Es wird auf der Grafikkarte ein Speicher reserviert, der alle Spuren der Spieler aufnehmen kann
	// Dynamisches Zeichen hat den Vorteil, dass es von dem Speicher und der Funktion her auf der Grafikkarte
	// bevorzugt wird und somit von der Geschwindigkeit her deutlich schneller ist.

	glBindVertexArray(m_arr);
	glBindBuffer(GL_ARRAY_BUFFER, m_buff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices * m_floats * m_quads, 0, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Batch::batchData(const std::vector<Shape*>& shapes) const
{
	/*
		Nach jedem Update wird in einer Liste aus Spuren (shapes)
		jede Spur evaluiert und die Daten an den Buffer auf der Grafikkarte weitergegeben.
	*/
	GLintptr offset = 0;
	glBindVertexArray(m_arr);
	glBindBuffer(GL_ARRAY_BUFFER, m_buff);

	for (auto i : shapes)
	{
		float x = static_cast<float>(i->getX());
		float y = static_cast<float>(i->getY());
		float w = static_cast<float>(i->getW());
		float h = static_cast<float>(i->getH());

		float r = i->getColor().x;
		float g = i->getColor().y;
		float b = i->getColor().z;

		float vertices[]
		{
			x,		y,		r, g, b,
			x + w,	y,		r, g, b,
			x + w,	y + h,	r, g, b,
			x + w,	y + h,	r, g, b,
			x,		y + h,	r, g, b,
			x,		y,		r, g, b
		};

		GLsizeiptr size = static_cast<GLsizeiptr>(sizeof(vertices));
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
		offset += static_cast<GLintptr>(size);
	}
}

void Batch::drawBatch() const
{
	glBindVertexArray(m_arr);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertices * m_quads));
}
