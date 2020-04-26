#include "batch.h"

Batch::Batch()
{
	glGenVertexArrays(1, &m_arr);
	glGenBuffers(1, &m_buff);

	glBindVertexArray(m_arr);
	glBindBuffer(GL_ARRAY_BUFFER, m_buff);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_vertices * m_floats * m_quads * sizeof(float)), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
		5 * sizeof(float), (const void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Batch::batchData(std::vector<Trail*>& trails) const
{
	GLintptr offset = 0;
	glBindVertexArray(m_arr);
	glBindBuffer(GL_ARRAY_BUFFER, m_buff);

	for (const auto i : trails)
	{
		float r = i->getColor().x;
		float g = i->getColor().y;
		float b = i->getColor().z;

		float x = static_cast<float>(i->getX());
		float y = static_cast<float>(i->getY());
		float w = static_cast<float>(i->getW());
		float h = static_cast<float>(i->getH());

		float data[]
		{
			x,		y,		r, g, b,
			x + w,	y,		r, g, b,
			x + w,	y + h,	r, g, b,
			x + w,	y + h,	r, g, b,
			x,		y + h,	r, g, b,
			x,		y,		r, g, b
		};

		GLsizeiptr size = static_cast<GLsizeiptr>(sizeof(data));
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		offset += static_cast<GLintptr>(size);
	}
}

void Batch::batchDraw() const
{
	glBindVertexArray(m_arr);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertices * m_quads));
}
