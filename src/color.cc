#include "GLFR/color.hh"

#include <glm/vec3.hpp>

namespace glfr
{
	glm::vec3 Color::RGB( const int r, const int g, const int b )
	{
		return glm::vec3 { r / 255.f, g / 255.f, b / 255.f };
	}
}
