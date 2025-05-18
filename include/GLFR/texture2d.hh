#ifndef GLFR_TEXTURE2D_HH
#define GLFR_TEXTURE2D_HH

#include <GL/glew.h>

namespace glfr
{
	class Texture2D
	{
	public:
		~Texture2D();

		static Texture2D RGB( const GLubyte r, const GLubyte g, const GLubyte b );
		static Texture2D RGB( const GLubyte c );

		GLuint GetTextureHandle() const;

	private:
		Texture2D() = default;
		GLuint m_texture;
	};
}

#endif

