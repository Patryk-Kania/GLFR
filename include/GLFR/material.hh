#ifndef GLFR_MATERIAL_HH
#define GLFR_MATERIAL_HH

#include <glm/vec3.hpp>

#include "texture2d.hh"

namespace glfr
{
	class Material
	{
	public:
		Material( const int r, const int g, const int b );
		Material( const int c) : Material( c, c, c) {}
		Material() : Material( 255 ) {}

		void SetBaseColor( const int r, const int g, const int b );
		void SetAlbedoTexture( const Texture2D &texture );

		glm::vec3 GetBaseColor() const;
		GLuint GetAlbedoTextureHandle() const;
	private:
		glm::vec3 m_baseColor;
		GLuint m_albedoTexture;
	};
}

#endif
