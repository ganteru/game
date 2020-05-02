#include "player.hpp"

Player::Player(int x, int y, Dir dir, const glm::vec3& color)
	: m_x{ x }, m_y{ y }, m_dir{ dir }, m_color{ color }
{
}

void Player::movement(const Input& input)
{
	// Setzt nur die Richtung basierend auf der Eingabe des Players
	if (input.keyLeft() && m_dir != Dir::RIGHT)
		m_dir = Dir::LEFT;
	if (input.keyRight() && m_dir != Dir::LEFT)
		m_dir = Dir::RIGHT;
	if (input.keyUp() && m_dir != Dir::DOWN)
		m_dir = Dir::UP;
	if (input.keyDown() && m_dir != Dir::UP)
		m_dir = Dir::DOWN;
}

void Player::update(int x, int y, int w, int h, int s)
{
	// Prueft die Richtung und veraendert die Position entsprechend
	switch (m_dir)
	{
	case Dir::LEFT:
		m_x -= s;
		break;
	case Dir::RIGHT:
		m_x += s;
		break;
	case Dir::UP:
		m_y += s;
		break;
	case Dir::DOWN:
		m_y -= s;
		break;
	default:
		break;
	}

	// Prueft, ob der Player das Spielfeld ueberschreitet.
	// Sollte dies der Fall sein, kommt der Player auf der anderen Seite des Spielfeldes heraus
	if (m_x < x)
		m_x = x + w - s;
	if (m_y < y)
		m_y = y + h - s;
	if (m_x > x + w)
		m_x = x;
	if (m_y > y + h)
		m_y = y;
}

int& Player::getX()
{
	return m_x;
}

void Player::setX(int x)
{
	m_x = x;
}

int& Player::getY()
{
	return m_y;
}

void Player::setY(int y)
{
	m_y = y;
}

Dir& Player::getDir()
{
	return m_dir;
}

void Player::setDir(Dir dir)
{
	m_dir = dir;
}

glm::vec3& Player::getColor()
{
	return m_color;
}