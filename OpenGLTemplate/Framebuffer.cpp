#include "Framebuffer.h"

#include "GL/glew.h"

Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &m_framebuffer);
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_framebuffer);
}

void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
}
