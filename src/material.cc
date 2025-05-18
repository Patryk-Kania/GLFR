#include "GLFR/material.hh"

#include <glm/vec3.hpp>

namespace glfr
{
	Material::Material( const int r, const int g, const int b )
	{
		m_baseColor = glm::vec3 { float( r ) / 255.f, float( g ) / 255.f, float( b ) / 255.f };
	}

	glm::vec3 Material::GetBaseColor() const
	{
		return m_baseColor;
	}
}
