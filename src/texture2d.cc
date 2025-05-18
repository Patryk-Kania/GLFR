#include "GLFR/texture2d.hh"

#include <utility>

#include <GL/glew.h>

namespace glfr
{

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_texture);
	}

	Texture2D Texture2D::RGB( const GLubyte r, const GLubyte g, const GLubyte b )
	{
		Texture2D texture;

		// 2x2 8_bit RGB texture
		const GLubyte pixels[] = 
		{
			r, g, b,
			r, g, b,
			r, g, b,
			r, g, b
		};

		glCreateTextures( GL_TEXTURE_2D, 1, &texture.m_texture );

		glTextureParameteri( texture.m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTextureParameteri( texture.m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTextureParameteri( texture.m_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTextureParameteri( texture.m_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glTextureStorage2D( texture.m_texture, 1, GL_RGB8, 2, 2 );
		glTextureSubImage2D( texture.m_texture, 0, 0, 0, 2, 2, GL_RGB, GL_UNSIGNED_BYTE, pixels );

		return texture;
	}

	Texture2D Texture2D::RGB( const GLubyte c )
	{
		return RGB( c, c, c );
	}
	
	GLuint Texture2D::GetTextureHandle() const
	{
		return m_texture;
	}
}
