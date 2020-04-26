#include "shader.h"

Shader::Shader(const char* vshader, const char* fshader)
{
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vshader, nullptr);
	glCompileShader(vertex);
	checkError("vertex", vertex);

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fshader, nullptr);
	glCompileShader(fragment);
	checkError("fragment", fragment);

	m_id = glCreateProgram();
	glAttachShader(m_id, vertex);
	glAttachShader(m_id, fragment);
	glLinkProgram(m_id);
	checkError("program", m_id);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::activate() const
{
	glUseProgram(m_id);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(getLocation(name), x, y, z);
}

void Shader::setVec3(const std::string& name, const glm::vec3& vec) const
{
	glUniform3fv(getLocation(name), 1, &vec[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, &mat[0][0]);
}

const GLuint Shader::getID() const
{
	return m_id;
}

GLint Shader::getLocation(const std::string& name) const
{
	return glGetUniformLocation(m_id, name.c_str());
}

void Shader::checkError(const std::string& type, GLuint shader) const
{
	int params;
	char infoLog[1024];

	if (type != "program")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
		if (!params)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &params);
		if (!params)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
		}
	}
}
