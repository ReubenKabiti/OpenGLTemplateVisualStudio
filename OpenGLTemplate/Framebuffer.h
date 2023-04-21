#pragma once
#include <cstdint>

class Framebuffer
{
private:
	uint32_t m_framebuffer;
public:
	Framebuffer();
	~Framebuffer();

	void bind();
};

