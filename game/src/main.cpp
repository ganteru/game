#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <random>
#include <ctime>

#include "import/stb_image.h"
#include "shader.h"
#include "trail.h"
#include "batch.h"
#include "input.h"
#include "player.h"
#include "sprite.h"

const int g_width	= 640;
const int g_height	= 480;

const int factor = 2;

bool field[g_width / factor][g_height / factor] = { 0 };

int generateNumber(int min, int max)
{
	static std::mt19937_64 s_mersenne{ static_cast<std::mt19937_64::result_type>(std::time(nullptr)) };
	std::uniform_int_distribution die{ min, max };
	return die(s_mersenne);
}

int WinMain(int argc, char** argv)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	int w, h;
	unsigned char* pixels = stbi_load("res/icon.png", &w, &h, 0, STBI_rgb_alpha);
	GLFWimage img{ w, h, pixels };


	GLFWwindow* window = glfwCreateWindow(g_width, g_height, "game", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetWindowIcon(window, 1, &img);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	Shader shader{ s_vertex_color, s_fragment_color };
	Shader sshader{ s_vertex_sprite, s_fragment_sprite };

	Sprite sprite{ "res/background.png" };

	Batch batch;

	std::vector<Trail*> trails;

	Player p1{ generateNumber(factor, g_width), generateNumber(factor, g_height), factor, factor, static_cast<Dir>(generateNumber(0, 3)), glm::vec3{ 1.0f, 0.0f, 0.0f } };

	Player p2{ generateNumber(factor, g_width), generateNumber(factor, g_height), factor, factor, static_cast<Dir>(generateNumber(0, 3)), glm::vec3{ 1.0f, 1.0f, 0.0f } };

	Input input{ window, GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN };
	Input input2{ window, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_W, GLFW_KEY_S };

	bool game = 1;

	static double delta = 0.0;
	static double last = 0.0;

	static double timer = 0.0;

	while (!glfwWindowShouldClose(window))
	{

		double current = glfwGetTime();
		delta = current - last;
		last = current;

		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

 
		if (input.keyLeft() && p1.getDir() != Dir::RIGHT)
			p1.setDir(Dir::LEFT);
		if (input.keyRight() && p1.getDir() != Dir::LEFT)
			p1.setDir(Dir::RIGHT);
		if (input.keyUp() && p1.getDir() != Dir::DOWN)
			p1.setDir(Dir::UP);
		if (input.keyDown() && p1.getDir() != Dir::UP)
			p1.setDir(Dir::DOWN);

		if (input2.keyLeft() && p2.getDir() != Dir::RIGHT)
			p2.setDir(Dir::LEFT);
		if (input2.keyRight() && p2.getDir() != Dir::LEFT)
			p2.setDir(Dir::RIGHT);
		if (input2.keyUp() && p2.getDir() != Dir::DOWN)
			p2.setDir(Dir::UP);
		if (input2.keyDown() && p2.getDir() != Dir::UP)
			p2.setDir(Dir::DOWN);


		if (game && timer <= 0.5)
		{
			p1.update(g_width, g_height, factor);
			p2.update(g_width, g_height, factor);

			if (field[p1.getX() / factor][p1.getY() / factor] == 1)
				game = 0;
			if (field[p2.getX() / factor][p2.getY() / factor] == 1)
				game = 0;
			field[p1.getX() / factor][p1.getY() / factor] = 1;
			field[p2.getX() / factor][p2.getY() / factor] = 1;

			trails.push_back(new Trail{ p1.getX(), p1.getY(), p1.getWidth(), p1.getHeight(), p1.getColor() });
			trails.push_back(new Trail{ p2.getX(), p2.getY(), p2.getWidth(), p2.getHeight(), p2.getColor() });
		}
		else
		{
			timer = 0.0;
		}



		glm::mat4 proj{ 1.0f };
		proj = glm::ortho(0.0f, static_cast<float>(g_width), 0.0f, static_cast<float>(g_height));

		sshader.activate();
		sshader.setMat4("proj", proj);
		sprite.draw();

		shader.activate();
		shader.setMat4("proj", proj);


		batch.batchData(trails);
		batch.batchDraw();

		glfwSwapBuffers(window);

		timer += delta;
	}

	stbi_image_free(pixels);

	glfwTerminate();
	return 0;
}