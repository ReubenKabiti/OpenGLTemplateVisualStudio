#include "Shader.h"
#include <iostream>
#include <cstdlib>

bool Shader::loadFromFile(const char * filename, GLint type)
{

	FILE* fp = nullptr;
	fopen_s(&fp, filename, "r");

	if (!fp)
		return false;

	const uint32_t shaderLen = 1024 * 10;
	char data[shaderLen];

	uint32_t numRead = fread(data, 1, shaderLen, fp);

	data[numRead] = '\0';

	bool created = create(data);
	fclose(fp);
	return created;
}

Shader::Shader(GLenum type)
{
	m_shader = glCreateShader(type);
}

Shader::~Shader()
{
	glDeleteShader(m_shader);
}

bool Shader::create(const char* src)
{
	glShaderSource(m_shader, 1, &src, nullptr);
	glCompileShader(m_shader);

	int32_t success;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(m_shader, 512, nullptr, infoLog);
		std::cerr << "Failed to compile shader: Error: " << infoLog;
		return false;
	}
	return true;
}

ShaderProgram::ShaderProgram()
{
	m_program = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_program);
}

bool ShaderProgram::create(const Shader& vs, const Shader& fs)
{
	glAttachShader(m_program, vs.m_shader);
	glAttachShader(m_program, fs.m_shader);

	glLinkProgram(m_program);

	int32_t success;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
		std::cerr << "Failed to link program: Error: " << infoLog;
		return false;
	}
	return true;
}
