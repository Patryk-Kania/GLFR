#ifndef GLFR_MESH_HH
#define GLFR_MESH_HH

#include <GL/glew.h>

#include "material.hh"

namespace glfr
{
	class Mesh
	{
	public:
		Mesh( const int numOfVertices, const GLfloat *vertices, const GLfloat *UVs, const GLfloat *normals,
		     const int numOfTriangles, const GLuint *triangles );
		Mesh( const Mesh &other );
		Mesh( Mesh &&other ) noexcept;

		Mesh& operator=( const Mesh &other );
		Mesh& operator=( Mesh &&other ) noexcept;

		~Mesh();

		static Mesh NewQuad();
		static Mesh NewCube();

		GLuint GetVAO() const;
		int GetNumOfTriangles() const;
	private:
		GLuint m_VAO, m_VBO, m_EBO;
		int *m_refCount;
		int m_numOfTriangles;

		void ReleaseHandles();
	};
}

#endif
