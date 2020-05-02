#include "renderer.hpp"

Renderer::Renderer(int width, int height) : m_width{ width }, m_height{ height }
{
	m_color_shader = new Shader{ "res/color.vert", "res/color.frag" };
	m_text_shader = new Shader{ "res/text.vert", "res/text.frag" };
	m_batch = new Batch{};
	m_text = new Text{ "res/ProggyCleanSZ.ttf", 16 };
	m_proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
}

Renderer::~Renderer()
{
	delete m_color_shader;
	delete m_text_shader;
	delete m_batch;
	delete m_text;
}

void Renderer::render(const std::string& text, float x, float y)
{
	m_text_shader->activate();
	m_text_shader->setMat4("proj", m_proj);
	m_text->draw(text, x, y);
}

void Renderer::render(const std::vector<Shape*>& shapes)
{
	m_color_shader->activate();
	m_color_shader->setMat4("proj", m_proj);
	m_batch->batchData(shapes);
	m_batch->drawBatch();
}

void Renderer::render(Menu& menu)
{
	m_text_shader->activate();
	m_text_shader->setMat4("proj", m_proj);
	m_text->draw("Press ENTER to get ready", static_cast<float>(m_width / 2 - 85), static_cast<float>(m_height / 2));
}
