#include "GLFR/material.hh"

#include <glm/vec3.hpp>

#include "GLFR/texture2d.hh"

namespace glfr
{
	Material::Material( const int r, const int g, const int b )
	{
		SetBaseColor( r, g, b );
	}

	void Material::SetBaseColor( const int r, const int g, const int b )
	{
		m_baseColor = glm::vec3 { float( r ) / 255.f, float( g ) / 255.f, float( b ) / 255.f };
	}

	void Material::SetAlbedoTexture( const Texture2D &texture )
	{
		m_albedoTexture = texture.GetTextureHandle();
	}

	glm::vec3 Material::GetBaseColor() const
	{
		return m_baseColor;
	}
	
	GLuint Material::GetAlbedoTextureHandle() const
	{
		return m_albedoTexture;
	}
}
