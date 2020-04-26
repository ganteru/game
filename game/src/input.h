#pragma once
#include <GLFW/glfw3.h>

class Input
{
private:
	GLFWwindow*	m_window;
	int			m_left;
	int			m_right;
	int			m_up;
	int			m_down;

public:
	Input(GLFWwindow* window, int left, int right, int up, int down);
	bool keyPressed(int key) const;
	bool keyLeft() const;
	bool keyRight() const;
	bool keyUp() const;
	bool keyDown() const;
};