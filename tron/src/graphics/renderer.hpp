#pragma once
#include <glm/glm.hpp>
#include "shader.hpp"
#include "batch.hpp"
#include "shape.hpp"
#include "text.hpp"
#include "game/menu.hpp"

/*
	Die Klasse enthält alle Shader
	und bindet je nach Zeichenauftrag
	den passenden Shader
*/
class Renderer
{
private:
	Shader*		m_color_shader;
	Shader*		m_text_shader;
	Batch*		m_batch;
	Text*		m_text;

	glm::mat4	m_proj;

	int m_width;
	int m_height;

public:
	Renderer(int width, int height);
	~Renderer();
	void render(const std::string& text, float x, float y);
	void render(const std::vector<Shape*>& shapes);
	void render(Menu& menu);
};