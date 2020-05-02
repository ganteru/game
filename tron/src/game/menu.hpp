#pragma once
#include "input.hpp"

/*
	Die Klasse Menu dient als vorlaeufer des Spiels,
	damit das Spiel nicht sofort startet, sondern wartet
	bis der Player mit ENTER das Spiel startet.
*/

class Menu
{
private:
	Input m_input;

	bool m_active = false;

public:
	Menu(const Input& input);
	void update();
	bool& getStatus();
	void setStatus(bool status);
};