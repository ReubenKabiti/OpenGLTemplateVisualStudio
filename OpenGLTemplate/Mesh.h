#pragma once

#include "GL/glew.h"
#include <memory>
#include <vector>

#include "Shader.h"
#include "BufferObject.h"

class Mesh
{
private:
	std::shared_ptr<ShaderProgram> m_shaderProgram;
	std::vector<float> m_vertices;
	std::vector<uint32_t> m_indices;

private:
	uint32_t m_vao;
	BufferObject<float> m_vbo;
	BufferObject<uint32_t> m_ebo;

	inline void bindVao() { glBindVertexArray(m_vao); }
	inline void unbindVao() { glBindVertexArray(0); }

public:

	Mesh();
	~Mesh();

	void setVertices(const std::vector<float>& newVertices);
	void setIndices(const std::vector<uint32_t>& newIndices);
	void setShaderProgram(const std::shared_ptr<ShaderProgram>& newShaderProgram);
	
	inline const std::shared_ptr<ShaderProgram>& getShaderProgram() const { return m_shaderProgram; }

	void configure(uint32_t location, uint32_t num, uint32_t stride, uint32_t start);
	void render();
};

