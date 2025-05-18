#ifndef GLFR_TEXTURE2D_HH
#define GLFR_TEXTURE2D_HH

#include <GL/glew.h>

namespace glfr
{
	class Texture2D
	{
	public:
		~Texture2D();

		static Texture2D CreateFromPixelArray( const int width, const int height, const GLubyte *pixels );
		static Texture2D SingleColor( const GLubyte r, const GLubyte g, const GLubyte b );
		static Texture2D SingleColor( const GLubyte c );

		static GLuint GetDefaultTextureHandle();

		GLuint GetTextureHandle() const;

	private:
		Texture2D() = default;
		GLuint m_texture;
		static Texture2D *s_defaultTexture;
	};
}

#endif

