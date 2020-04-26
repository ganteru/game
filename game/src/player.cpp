#include "player.h"

Player::Player(const int& x, const int& y, const int& w, const int& h, const Dir& dir, const glm::vec3& color)
	: m_x{ x }, m_y{ y }, m_w{ w }, m_h{ h }, m_dir{ dir }, m_color{ color }
{
}

void Player::update(int width, int height, int speed)
{
	switch (m_dir)
	{
	case Dir::LEFT:
		m_x -= speed;
		break;
	case Dir::RIGHT:
		m_x += speed;
		break;
	case Dir::UP:
		m_y += speed;
		break;
	case Dir::DOWN:
		m_y -= speed;
		break;
	default:
		break;
	}

	if (m_x < 0)
		m_x = width - m_w;
	if (m_y < 0)
		m_y = height - m_h;
	if (m_x >= width)
		m_x = 0;
	if (m_y >= height)
		m_y = 0;
}

int& Player::getX()
{
	return m_x;
}

void Player::setX(const int& x)
{
	m_x = x;
}

int& Player::getY()
{
	return m_y;
}

void Player::setY(const int& y)
{
	m_y = y;
}

int& Player::getWidth()
{
	return m_w;
}

void Player::setWidth(const int& w)
{
	m_w = w;
}

int& Player::getHeight()
{
	return m_h;
}

void Player::setHeight(const int& h)
{
	m_h = h;
}

Dir& Player::getDir()
{
	return m_dir;
}

void Player::setDir(const Dir& dir)
{
	m_dir = dir;
}

glm::vec3& Player::getColor()
{
	return m_color;
}

void Player::setColor(const glm::vec3& color)
{
	m_color = color;
}