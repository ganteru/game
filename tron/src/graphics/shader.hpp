#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>

class Shader
{
private:
	GLuint m_id;

public:
	Shader(const std::string& vpath, const std::string& fpath);
	// Shader muss gebunden werden, damit OpenGL nach diesem Shader zeichnen kann
	void		activate() const;

	// Methoden um die Uniformen in den Shadern setzen zu können
	void		setVec3(const std::string& name, const glm::vec3& vec) const;
	void		setMat4(const std::string& name, const glm::mat4& mat) const;

private:
	// Gibt die Position einer Uniform aus dem Shader zurück
	GLint		getLocation(const std::string& name) const;

	// Laedt eine Shaderdatei und gibt den Inhalt als string zurück
	std::string parseFile(const std::string& path) const;

	// Prueft den Status der Shaders in OpenGL auf Fehlercodes
	void		checkError(const std::string& type, GLuint shader) const;
};