#ifndef GLFR_TEXTURE2D_HH
#define GLFR_TEXTURE2D_HH

#include <GL/glew.h>

namespace glfr
{
	class Texture2D
	{
	public:
		Texture2D() : m_handle{ 0 }, m_refCount{ nullptr } {}
		Texture2D( const Texture2D &other );
		Texture2D( Texture2D &&other ) noexcept;

		Texture2D& operator=( const Texture2D &other );
		Texture2D& operator=( Texture2D &&other ) noexcept;

		~Texture2D();

		static Texture2D FromPixelsRGBA( const GLubyte *pixels, const int width, const int height );
		static Texture2D FromColorRGBA( const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a );
		//static Texture2D FromFile( const char *file, const int width, const int height, const GLenum format );

		void Bind( GLenum unit = GL_TEXTURE0 ) const;
		bool IsValid() const;

	private:
		GLuint m_handle;
		int *m_refCount;

		void ReleaseHandle();
	};
}

#endif

