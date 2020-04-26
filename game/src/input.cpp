#include "input.h"

Input::Input(GLFWwindow* window, int left, int right, int up, int down)
	: m_window{ window }, m_left{ left }, m_right{ right }, m_up{ up }, m_down{ down }
{
}

bool Input::keyPressed(int key) const
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool Input::keyLeft() const
{
	return glfwGetKey(m_window, m_left) == GLFW_PRESS;
}

bool Input::keyRight() const
{
	return glfwGetKey(m_window, m_right) == GLFW_PRESS;
}

bool Input::keyUp() const
{
	return glfwGetKey(m_window, m_up) == GLFW_PRESS;
}

bool Input::keyDown() const
{
	return glfwGetKey(m_window, m_down) == GLFW_PRESS;
}
