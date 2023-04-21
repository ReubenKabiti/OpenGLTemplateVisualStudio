#pragma once
#include <cstdint>
#include "GL/glew.h"

class Shader
{
private:
	friend class ShaderProgram;

	uint32_t m_shader;

public:

	Shader(GLenum type);
	~Shader();

	bool loadFromFile(const char* filename, GLint type);
	bool create(const char* src);
};

class ShaderProgram
{
private:

	uint32_t m_program;

public:

	ShaderProgram();
	~ShaderProgram();

	bool create(const Shader& vs, const Shader& fs);

	inline void use()
	{
		glUseProgram(m_program);
	}

	inline static void useNone(){ glUseProgram(0); }
};
