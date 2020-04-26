#include "sprite.h"

Sprite::Sprite(const std::string& path)
{
	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, 0, STBI_rgb_alpha);
	if (data)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	float w = static_cast<float>(m_width);
	float h = static_cast<float>(m_height);

	float vertices[]
	{
		0.0f, 0.0f, 0.0f, 0.0f,
		w, 0.0f, 1.0f, 0.0f,
		w, h, 1.0f, 1.0f,
		w, h, 1.0f, 1.0f,
		0, h, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

	GLuint buff;
	glGenVertexArrays(1, &m_arr);
	glGenBuffers(1, &buff);

	glBindVertexArray(m_arr);
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Sprite::draw() const
{
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glBindVertexArray(m_arr);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
