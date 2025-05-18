#include "GLFR/mesh.hh"

#include <GL/glew.h>

namespace glfr
{
	Mesh::Mesh( const int numOfVertices, const GLfloat *vertices, const GLfloat *UVs,
		   const int numOfTriangles, const GLuint *triangles )
	{
		glCreateVertexArrays( 1, &m_VAO );
		glCreateBuffers( 1, &m_VBO );
		glCreateBuffers( 1, &m_EBO );

		// 3 floats for position + 2 floats for UVs
		GLfloat vertexData[numOfVertices * (3 + 2)];
		for( int i = 0; i < numOfVertices; i++ )
		{
			int vertexIndex = i * 5;
			int positionIndex = i * 3;
			int UVIndex = i * 2;

			vertexData[vertexIndex + 0] = vertices[positionIndex + 0]; 
			vertexData[vertexIndex + 1] = vertices[positionIndex + 1]; 
			vertexData[vertexIndex + 2] = vertices[positionIndex + 2]; 

			vertexData[vertexIndex + 3] = UVs[UVIndex + 0]; 
			vertexData[vertexIndex + 4] = UVs[UVIndex + 1]; 
		}

		glNamedBufferStorage( m_VBO, sizeof(GLfloat) * numOfVertices * (3 + 2), vertexData, 0 );
		glNamedBufferStorage( m_EBO, sizeof(GLuint) * numOfTriangles * 3, triangles, 0 );

		glVertexArrayVertexBuffer( m_VAO, 0, m_VBO, 0, (3 + 2) * sizeof( GLfloat ) );
		glVertexArrayElementBuffer( m_VAO, m_EBO );

		glEnableVertexArrayAttrib( m_VAO, 0 ); // Attrib 0 = Position
		glVertexArrayAttribFormat( m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0 );

		glEnableVertexArrayAttrib( m_VAO, 1 ); // Attrib 1 = UV
		glVertexArrayAttribFormat( m_VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat) );

		glVertexArrayAttribBinding( m_VAO, 0, 0 );
		glVertexArrayAttribBinding( m_VAO, 1, 0 );

		m_numOfTriangles = numOfTriangles;
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays( 1, &m_VAO );
		glDeleteBuffers( 1, &m_VBO );
		glDeleteBuffers( 1, &m_EBO );
	}

	void Mesh::AttachMaterial(Material material)
	{
		m_attachedMaterial = material;
	}
	
	GLuint Mesh::GetVAO() const
	{
		return m_VAO;
	}

	int Mesh::GetNumOfTriangles() const
	{
		return m_numOfTriangles;
	}

	Material Mesh::GetAttachedMaterial() const
	{
		return m_attachedMaterial;
	}
}
