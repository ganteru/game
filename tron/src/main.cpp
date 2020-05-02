#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <random>
#include <ctime>
#include "game/player.hpp"
#include "game/input.hpp"
#include "graphics/renderer.hpp"
#include "game/menu.hpp"


int WinMain()
{

	// Initialisierung von GLFW
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	const int w = 640;
	const int h = 480;

	// Nach erfolgreicher Initialisierung von GLFW kann ein Fenster erstellt werden.

	GLFWwindow* window = glfwCreateWindow(w, h, "tron", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Das erstellte Fenster braucht nun einen OpenGL Context damit OpenGL Grafik an das Fenster senden kann.
	glfwMakeContextCurrent(window);

	// Initialisierung von GLAD, um die Funktionen von OpenGL aus der Grafikkarte zu laden.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}


	// Erstellung der Eingabe mit den dazugehörigen Tasten
	Input i1{ window, GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN };
	Input i2{ window, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_S };


	/*
		Mersenne ist ein Algorthimus fuer Zufallszahlen.
		Es wird sowohl die Position der Spieler mit diesen Zufallszahlen initialisiert,
		als auch die Richtung der Spieler.
	*/

	std::mt19937_64 mersenne{ static_cast<std::mt19937_64::result_type>(std::time(nullptr)) };
	std::uniform_int_distribution posx{ 1, w };
	std::uniform_int_distribution posy{ 1, h };
	std::uniform_int_distribution dir{ 0, 3 };

	
	Renderer r{ w, h };
	Player p1{ posx(mersenne), posy(mersenne), static_cast<Dir>(dir(mersenne)), glm::vec3{1.0f, 0.0f, 0.0f} };
	Player p2{ posx(mersenne), posy(mersenne), static_cast<Dir>(dir(mersenne)), glm::vec3{1.0f, 1.0f, 0.0f} };

	Menu menu{ i1 };

	// Eine Liste fuer das ansammeln von Spuren der Spieler
	std::vector<Shape*> shapes;

	// Das Spielfeld mit der Groesse des Fensters
	bool field[w][h] = { 0 };


	// Abbruchbedingungen und finale Ausgabe des Gewinners
	bool game = true;
	std::string endText = "";

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glClear(GL_COLOR_BUFFER_BIT);
		if (!menu.getStatus())
		{
			r.render(menu);
			menu.update();

		}
		else
		{
			if (!game)
			{
				// Sollte das Spiel vorbei sind, wird aufgeraeumt.
				for (auto i : shapes)
					delete i;
				shapes.clear();

				continue;
			}
			else
			{
				// Solange das Spiel laeuft, sollen die Spieler geupdated werden
				p1.movement(i1);
				p2.movement(i2);
				p1.update(0, 0, w, h, 1);
				p2.update(0, 0, w, h, 1);

				// Befindet sich ein Spieler auf einem Feld das bereits besetzt ist, ist das Spiel vorbei
				// und dieser Spieler verliert somit das Spiel.

				if (field[p1.getX()][p1.getY()] == 1)
				{
					game = false;
					endText = "Player yellow wins";
				}

				if (field[p2.getX()][p2.getY()] == 1)
				{
					game = false;
					endText = "Player red wins";
				}

				// Sonst werden die Felder auf dem die Spieler landen als besetzt markiert.
				field[p1.getX()][p1.getY()] = 1;
				field[p2.getX()][p2.getY()] = 1;

				// Für jedes Feld auf das sich ein Spieler befindet wird eine Spur gezeichnet.
				shapes.push_back(new Shape{ p1.getX(), p1.getY(), 1, 1, p1.getColor() });
				shapes.push_back(new Shape{ p2.getX(), p2.getY(), 1, 1, p2.getColor() });


				// Am Ende werden einmal alle Spuren gezeichnet
				r.render(shapes);
			}
		}

		// Sollte das Spiel vorbei sein wird der Gewinner ausgegeben
		if (endText != "")
		{
			glClear(GL_COLOR_BUFFER_BIT);
			r.render(endText, static_cast<float>(w / 2 - 85), static_cast<float>(h / 2));
			r.render("Press ESCAPE to close", static_cast<float>(w / 2 - 85), static_cast<float>(h / 2 - 25));
		}
		glfwSwapBuffers(window);
	}

	// Raeumt vor beenden des Programms nochmal die Spuren auf
	for (auto i : shapes)
		delete i;
	shapes.clear();

	glfwTerminate();
	return 0;
}