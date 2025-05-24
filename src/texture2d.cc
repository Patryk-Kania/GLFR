#include "GLFR/texture2d.hh"

#include <cassert>

#include <utility>
#include <iostream>

#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace glfr
{
	Texture2D::Texture2D( const Texture2D &other ) : m_handle{ other.m_handle }, m_refCount{ other.m_refCount }
	{
		if( m_refCount )
			(*m_refCount)++;
	}

	Texture2D::Texture2D( Texture2D &&other ) noexcept
		: m_handle{ other.m_handle }, m_refCount{ other.m_refCount }
	{
		other.m_handle = 0;
		other.m_refCount = nullptr;
	}

	Texture2D& Texture2D::operator=( const Texture2D &other )
	{
		if( this != &other )
		{
			ReleaseHandle();

			m_handle = other.m_handle;
			m_refCount = other.m_refCount;

			if( m_refCount )
				(*m_refCount)++;

		}

		return *this;
	}

	Texture2D& Texture2D::operator=( Texture2D &&other ) noexcept
	{
		if( this != &other )
		{
			ReleaseHandle();

			m_handle = other.m_handle;
			m_refCount = other.m_refCount;

			other.m_handle = 0;
			other.m_refCount = nullptr;
		}

		return *this;
	}

	Texture2D::~Texture2D()
	{
		ReleaseHandle();
	}

		
	Texture2D Texture2D::FromPixelsRGBA( const GLubyte *pixels, const int width, const int height )
	{
		Texture2D texture;
		glCreateTextures( GL_TEXTURE_2D, 1, &texture.m_handle );

		glTextureParameteri( texture.m_handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTextureParameteri( texture.m_handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTextureParameteri( texture.m_handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTextureParameteri( texture.m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glTextureStorage2D( texture.m_handle, 1, GL_RGBA8, width, height );
		glTextureSubImage2D( texture.m_handle, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

		texture.m_refCount = new int{ 1 };

		return texture;
	}

	Texture2D Texture2D::FromColorRGBA( const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a )
	{
		const GLubyte pixels[] = 
		{
			r, g, b, a,
			r, g, b, a,
			r, g, b, a,
			r, g, b, a,
		};

		return FromPixelsRGBA( pixels, 2, 2 );
	}

	Texture2D Texture2D::FromFile( const char *file, bool flipVertically )
	{
		stbi_set_flip_vertically_on_load( flipVertically );
		int width, height, channels;
		unsigned char *data = stbi_load( file, &width, &height, &channels, 0 );

		if( !data )
		{
			std::cerr << "Failed to load \"" << file << "\" texture file.\n";
			return Texture2D();
		}

		GLenum format;
		GLenum internalFormat;

		switch (channels) {
			case 1:
				format = internalFormat = GL_RED;
				break;
			case 2:
				format = internalFormat = GL_RG;
				break;
			case 3:
				format = GL_RGB;
				internalFormat = GL_RGB8;
				break;
			case 4:
				format = GL_RGBA;
				internalFormat = GL_RGBA8;
				break;
			default:
				std::cerr << "Unsupported number of channels: " << channels << " [texture: <" << file << ">]\n";
				stbi_image_free(data);
				return Texture2D();
		}

		Texture2D texture;
		glCreateTextures( GL_TEXTURE_2D, 1, &texture.m_handle );

		glTextureParameteri( texture.m_handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTextureParameteri( texture.m_handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTextureParameteri( texture.m_handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTextureParameteri( texture.m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTextureStorage2D( texture.m_handle, 1, internalFormat, width, height );
		glTextureSubImage2D( texture.m_handle, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data );

		texture.m_refCount = new int{ 1 };

		stbi_image_free( data );

		return texture;
	}

	void Texture2D::Bind( GLenum unit ) const
	{
		glBindTextureUnit( unit, m_handle );
	}

	bool Texture2D::IsValid() const
	{
		return m_handle != 0;
	}

	void Texture2D::ReleaseHandle()
	{
		if( m_refCount && --(*m_refCount) == 0 )
		{
			glDeleteTextures( 1, &m_handle );
			delete m_refCount;
		}
		
		m_refCount = nullptr;
		m_handle = 0;
	}
}
