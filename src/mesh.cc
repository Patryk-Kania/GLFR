#include "GLFR/mesh.hh"

#include <GL/glew.h>

namespace glfr
{
	Mesh::Mesh(const int numOfVertices, const GLfloat *vertices,
		   const int numOfTriangles, const GLuint *triangles)
	{
		glCreateVertexArrays(1, &m_VAO);
		glCreateBuffers(1, &m_VBO);
		glCreateBuffers(1, &m_EBO);

		glNamedBufferStorage(m_VBO, sizeof(GLfloat) * numOfVertices * 3, vertices, 0);
		glNamedBufferStorage(m_EBO, sizeof(GLuint) * numOfTriangles * 3, triangles, 0);

		glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, 3 * sizeof(GLfloat));
		glVertexArrayElementBuffer(m_VAO, m_EBO);

		glEnableVertexArrayAttrib(m_VAO, 0); // Attrib 0 = Position
		glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

		glVertexArrayAttribBinding(m_VAO, 0, 0);

		m_numOfTriangles = numOfTriangles;
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}
	
	GLuint Mesh::GetVAO() const
	{
		return m_VAO;
	}

	int Mesh::GetNumOfTriangles() const
	{
		return m_numOfTriangles;
	}
}
