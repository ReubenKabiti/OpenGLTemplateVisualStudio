#include "Mesh.h"

Mesh::Mesh()
{
	glGenVertexArrays(1, &m_vao);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::setVertices(const std::vector<float>& newVertices)
{
	m_vertices = newVertices;

	bindVao();
	m_vbo.init(GL_ARRAY_BUFFER);
	m_vbo.bind();
	m_vbo.upload(newVertices.data(), newVertices.size() * 4, GL_STATIC_DRAW);
	m_vbo.unbind();
	unbindVao();
}

void Mesh::setIndices(const std::vector<uint32_t>& newIndices)
{
	m_indices = newIndices;

	bindVao();
	m_ebo.init(GL_ELEMENT_ARRAY_BUFFER);
	m_ebo.bind();
	m_ebo.upload(newIndices.data(), newIndices.size() * 4, GL_STATIC_DRAW);
	m_ebo.unbind();
	unbindVao();
}

void Mesh::setShaderProgram(const std::shared_ptr<ShaderProgram>& newShaderProgram)
{
	m_shaderProgram = newShaderProgram;
}

void Mesh::configure(uint32_t location, uint32_t num, uint32_t stride, uint32_t start)
{
	bindVao();
	m_vbo.bind();
	m_ebo.bind();

	glVertexAttribPointer(location, num, GL_FLOAT, GL_FALSE, stride, (void*)(start * 4));
	glEnableVertexAttribArray(location);

	m_ebo.unbind();
	m_vbo.unbind();
	unbindVao();
}

void Mesh::render()
{
	bindVao();
	m_vbo.bind();
	m_ebo.bind();

	m_shaderProgram->use();
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
}
