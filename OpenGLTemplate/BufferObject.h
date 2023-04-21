#pragma once

#include "GL/glew.h"

template<class T>
class BufferObject
{
private:

	GLenum m_target;
	uint32_t m_buffer;

public:

	void init(GLenum target)
	{
		glGenBuffers(1, &m_buffer);
		m_target = target;
	}

	void destroy() { glDeleteBuffers(1, &m_buffer); }

	void bind() { glBindBuffer(m_target, m_buffer); }

	void upload(const T* data, uint32_t size, GLenum usage)
	{
		bind();
		glBufferData(m_target, size, data, usage);
		unbind();
	}

	void unbind() { glBindBuffer(m_target, 0); }
};

