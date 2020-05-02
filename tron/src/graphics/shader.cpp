#include "shader.hpp"

Shader::Shader(const std::string& vpath, const std::string& fpath)
{

	// Umwandlung der Shaderdateien in ein von OpenGL akzeptiertes Format
	std::string vsource = parseFile(vpath);
	std::string fsource = parseFile(fpath);

	const char* vshader = vsource.c_str();
	const char* fshader = fsource.c_str();

	// Erstellen der Shader und zuordnung der Shaderinfo aus den Dateien

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vshader, nullptr);
	glCompileShader(vertex);
	checkError("vertex", vertex);

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fshader, nullptr);
	glCompileShader(fragment);
	checkError("fragment", fragment);

	// Der Vertex- und Fragmentshader werden einem Shaderprogramm hinzugefügt

	m_id = glCreateProgram();
	glAttachShader(m_id, vertex);
	glAttachShader(m_id, fragment);
	glLinkProgram(m_id);
	checkError("program", m_id);

	// Wenn das Shaderprogramm alle erstellen Shaders besitzt, koennen diese gelöscht werden

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::activate() const
{
	glUseProgram(m_id);
}

void Shader::setVec3(const std::string& name, const glm::vec3& vec) const
{
	glUniform3fv(getLocation(name), 1, glm::value_ptr(vec));
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

GLint Shader::getLocation(const std::string& name) const
{
	return glGetUniformLocation(m_id, name.c_str());
}

std::string Shader::parseFile(const std::string& path) const
{
	// Erstellt einen Stream der Strings als input nimmt.
	std::stringstream stream;

	// Offnet eine Datei 
	std::ifstream file;
	file.open(path);

	// Der Inhalt(buffer) der Datei wird als string direkt dem stream übergeben
	stream << file.rdbuf();
	file.close();

	// Der Inhalt des Streams und somit der Datei wird als string zurueck gegeben
	return stream.str();
}

void Shader::checkError(const std::string& type, GLuint shader) const
{
	int params;
	char infoLog[1024];

	if (type != "program")
	{
		// Prueft nach dem Status eines Shaders
		glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
		// Wird die Variable params einen Wert zurueckgeben, besteht ein Fehlercode
		if (!params)
		{
			// Anhand des Fehlercodes wird eine Info aus OpenGL gezogen und in infoLog reingepackt
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
