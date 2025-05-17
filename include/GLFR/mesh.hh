#ifndef GLFR_MESH_HH
#define GLFR_MESH_HH

#include <GL/glew.h>

namespace glfr
{
	class Mesh
	{
	public:
		Mesh(const int numOfVertices, const GLfloat *vertices,
		     const int numOfTriangles, const GLuint *triangles);
		~Mesh();

		GLuint GetVAO() const;
		int GetNumOfTriangles() const;
	private:
		GLuint m_VAO, m_VBO, m_EBO;
		int m_numOfTriangles;
	};
}

#endif
