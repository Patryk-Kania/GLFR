#ifndef GLFR_MATERIAL_HH
#define GLFR_MATERIAL_HH

#include <glm/vec3.hpp>

namespace glfr
{
	class Material
	{
	public:
		Material( const int r, const int g, const int b );
		Material() : Material( 137, 207, 240 ) {}

		glm::vec3 GetBaseColor() const;

	private:
		glm::vec3 m_baseColor;
	};
}

#endif
