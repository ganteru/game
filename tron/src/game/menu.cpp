#include "menu.hpp"

Menu::Menu(const Input& input) : m_input{ input }
{
}

void Menu::update()
{
	if (m_input.keyPressed(GLFW_KEY_ENTER))
		m_active = true;
}

bool& Menu::getStatus()
{
	return m_active;
}

void Menu::setStatus(bool status)
{
	m_active = status;
}
