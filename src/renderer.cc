#include "GLFR/renderer.hh"

#include <GL/glew.h>

namespace glfr
{
	void Renderer::Init(const int viewportWidth, const int viewportHeight)
	{
		glViewport(0, 0, viewportWidth, viewportHeight);
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::ClearColor(const int r, const int g, const int b)
	{
		glClearColor(r / 255.f, g / 255.f, b / 255.f, 1.0f);	
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::ClearColor(const int c)
	{
		ClearColor(c, c, c);
	}

	void Renderer::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}
}
