#ifndef GLFR_COLOR_HH
#define GLFR_COLOR_HH

#include <glm/vec3.hpp>

namespace glfr
{
	class Color
	{
	public:
		static glm::vec3 RGB( const int r, const int g, const int b );
	};
}

#endif
