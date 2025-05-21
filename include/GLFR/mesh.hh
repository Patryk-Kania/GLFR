#ifndef GLFR_MESH_HH
#define GLFR_MESH_HH

#include <GL/glew.h>

#include "material.hh"

namespace glfr
{
	class Mesh
	{
	public:
		Material material;

		Mesh( const int numOfVertices, const GLfloat *vertices, const GLfloat *UVs,
		     const int numOfTriangles, const GLuint *triangles );
		~Mesh();

		static Mesh NewQuad();
		static Mesh NewCube();

		GLuint GetVAO() const;
		int GetNumOfTriangles() const;
	private:
		GLuint m_VAO, m_VBO, m_EBO;
		int m_numOfTriangles;
	};
}

#endif
