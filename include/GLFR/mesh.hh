#ifndef GLFR_MESH_HH
#define GLFR_MESH_HH

#include <GL/glew.h>

#include "material.hh"

namespace glfr
{
	class Mesh
	{
	public:
		Mesh( const int numOfVertices, const GLfloat *vertices,
		     const int numOfTriangles, const GLuint *triangles );
		~Mesh();

		void AttachMaterial(Material material);

		GLuint GetVAO() const;
		int GetNumOfTriangles() const;
		Material GetAttachedMaterial() const;
	private:
		GLuint m_VAO, m_VBO, m_EBO;
		int m_numOfTriangles;
		Material m_attachedMaterial;
	};
}

#endif
