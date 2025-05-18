#include "GLFR/texture2d.hh"

#include <utility>

#include <GL/glew.h>

namespace glfr
{

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_texture);
	}

	Texture2D Texture2D::CreateFromPixelArray( const int width, const int height, const GLubyte *pixels )
	{
		Texture2D texture;
		glCreateTextures( GL_TEXTURE_2D, 1, &texture.m_texture );

		glTextureParameteri( texture.m_texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTextureParameteri( texture.m_texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTextureParameteri( texture.m_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTextureParameteri( texture.m_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glTextureStorage2D( texture.m_texture, 1, GL_RGBA8, width, height );
		glTextureSubImage2D( texture.m_texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

		return texture;
	}

	Texture2D Texture2D::SingleColor( const GLubyte r, const GLubyte g, const GLubyte b )
	{
		// 2x2 8_bit RGB texture
		const GLubyte pixels[] = 
		{
			r, g, b, 255,
			r, g, b, 255,
			r, g, b, 255,
			r, g, b, 255
		};

		return CreateFromPixelArray(2, 2, pixels);
	}

	Texture2D Texture2D::SingleColor( const GLubyte c )
	{
		return SingleColor( c, c, c );
	}

	
	GLuint Texture2D::GetTextureHandle() const
	{
		return m_texture;
	}
}
