#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

static const char* s_vertex_color
{
	"#version 330 core\n"
	"layout (location = 0) in vec2 pos;\n"
	"layout (location = 1) in vec3 col;\n"
	"out vec3 color;\n"
	"uniform mat4 proj;\n"
	"void main()\n"
	"{\n"
	"color = col;"
	"gl_Position = proj * vec4(pos, 0.0, 1.0);\n"
	"}"
};

static const char* s_fragment_color
{
	"#version 330 core\n"
	"out vec4 fragment;\n"
	"in vec3 color;\n"
	"void main()\n"
	"{\n"
	"fragment = vec4(color, 1.0);\n"
	"}"
};

static const char* s_vertex_sprite
{
	"#version 330 core\n"
	"layout (location = 0) in vec2 pos;\n"
	"layout (location = 1) in vec2 tex;\n"
	"out vec2 texel;\n"
	"uniform mat4 proj;\n"
	"void main()\n"
	"{\n"
	"texel = tex;"
	"gl_Position = proj * vec4(pos, 0.0, 1.0);\n"
	"}"
};

static const char* s_fragment_sprite
{
	"#version 330 core\n"
	"out vec4 fragment;\n"
	"in vec2 texel;\n"
	"uniform sampler2D img;\n"
	"void main()\n"
	"{\n"
	"vec4 temp = texture(img, texel);\n"
	"if (temp.a < 0.1)\n"
	"discard;\n"
	"fragment = temp;\n"
	"}"
};


class Shader
{
private:
	GLuint m_id;

public:
	Shader(const char* vshader, const char* fshader);
	void			activate() const;
	void			setVec3(const std::string& name, float x, float y, float z) const;
	void			setVec3(const std::string& name, const glm::vec3& vec) const;
	void			setMat4(const std::string& name, const glm::mat4& mat) const;
	const GLuint	getID() const;

private:
	GLint			getLocation(const std::string& name) const;
	void			checkError(const std::string& type, GLuint shader) const;
};