#include "GLFR/mesh.hh"

#include <GL/glew.h>

#include "default_meshes.hh"

namespace glfr
{
	Mesh::Mesh( const int numOfVertices, const GLfloat *vertices, const GLfloat *UVs, const GLfloat *normals,
		   const int numOfTriangles, const GLuint *triangles )
	{
		glCreateVertexArrays( 1, &m_VAO );
		glCreateBuffers( 1, &m_VBO );
		glCreateBuffers( 1, &m_EBO );

		// 3 floats for position + 2 floats for UVs + 3 floats for normals
		GLfloat vertexData[numOfVertices * (3 + 2 + 3)];
		for( int i = 0; i < numOfVertices; i++ )
		{
			int vertexIndex = i * 8;
			int positionIndex = i * 3;
			int UVIndex = i * 2;
			int normalIndex = i * 3;

			vertexData[vertexIndex + 0] = vertices[positionIndex + 0]; 
			vertexData[vertexIndex + 1] = vertices[positionIndex + 1]; 
			vertexData[vertexIndex + 2] = vertices[positionIndex + 2]; 

			vertexData[vertexIndex + 3] = UVs[UVIndex + 0]; 
			vertexData[vertexIndex + 4] = UVs[UVIndex + 1]; 

			vertexData[vertexIndex + 5] = normals[normalIndex + 0]; 
			vertexData[vertexIndex + 6] = normals[normalIndex + 1]; 
			vertexData[vertexIndex + 7] = normals[normalIndex + 2]; 
		}

		glNamedBufferStorage( m_VBO, sizeof(vertexData), vertexData, 0 );
		glNamedBufferStorage( m_EBO, sizeof(GLuint) * numOfTriangles * 3, triangles, 0 );

		glVertexArrayVertexBuffer( m_VAO, 0, m_VBO, 0, (3 + 2 + 3) * sizeof( GLfloat ) );
		glVertexArrayElementBuffer( m_VAO, m_EBO );

		glEnableVertexArrayAttrib( m_VAO, 0 ); // Attrib 0 = Position
		glVertexArrayAttribFormat( m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0 );

		glEnableVertexArrayAttrib( m_VAO, 1 ); // Attrib 1 = UV
		glVertexArrayAttribFormat( m_VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ) );

		glEnableVertexArrayAttrib( m_VAO, 2 ); // Attrib 2 = Normal
		glVertexArrayAttribFormat( m_VAO, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ) );

		glVertexArrayAttribBinding( m_VAO, 0, 0 );
		glVertexArrayAttribBinding( m_VAO, 1, 0 );
		glVertexArrayAttribBinding( m_VAO, 2, 0 );

		m_numOfTriangles = numOfTriangles;

		m_refCount = new int{ 1 };
	}

	Mesh::Mesh( const Mesh &other ) : m_VAO{ other.m_VAO }, m_VBO{ other.m_VBO }, m_EBO{ other.m_EBO },
		m_numOfTriangles{ other.m_numOfTriangles }, m_refCount{ other.m_refCount }
	{
		if( m_refCount )
			(*m_refCount)++;
	}

	Mesh::Mesh( Mesh &&other ) noexcept : m_VAO{ other.m_VAO }, m_VBO{ other.m_VBO }, m_EBO{ other.m_EBO },
		m_numOfTriangles{ other.m_numOfTriangles }, m_refCount{ other.m_refCount }
	{
		other.m_VAO = 0;
		other.m_VBO = 0;
		other.m_EBO = 0;
		other.m_numOfTriangles = 0;
		other.m_refCount = nullptr;
	}

	Mesh& Mesh::operator=( const Mesh &other )
	{
		if( this != &other )
		{
			ReleaseHandles();

			m_VAO = other.m_VAO;
			m_VBO = other.m_VBO;
			m_EBO = other.m_EBO;
			m_numOfTriangles = other.m_numOfTriangles;
			m_refCount = other.m_refCount;

			if( m_refCount )
				(*m_refCount)++;
		}

		return *this;
	}

	Mesh& Mesh::operator=( Mesh &&other ) noexcept
	{

		if( this != &other )
		{
			ReleaseHandles();

			m_VAO = other.m_VAO;
			m_VBO = other.m_VBO;
			m_EBO = other.m_EBO;
			m_numOfTriangles = other.m_numOfTriangles;
			m_refCount = other.m_refCount;

			other.m_VAO = 0;
			other.m_VBO = 0;
			other.m_EBO = 0;
			other.m_numOfTriangles = 0;
			other.m_refCount = nullptr;
		}

		return *this;
	}

	Mesh::~Mesh()
	{
		ReleaseHandles();
	}

	Mesh Mesh::NewQuad()
	{
		static Mesh defaultQuad{ 4, Quad::vertices, Quad::UVs, Quad::normals, 2, Quad::triangles };
		return defaultQuad;
	}

	Mesh Mesh::NewCube()
	{
		static Mesh defaultCube{ 24, Cube::vertices, Cube::UVs, Cube::normals, 12, Cube::triangles };
		return defaultCube;
	}

	GLuint Mesh::GetVAO() const
	{
		return m_VAO;
	}

	int Mesh::GetNumOfTriangles() const
	{
		return m_numOfTriangles;
	}

	void Mesh::ReleaseHandles()
	{
		if( m_refCount && --(*m_refCount) == 0)
		{
			glDeleteVertexArrays( 1, &m_VAO );
			glDeleteBuffers( 1, &m_VBO );
			glDeleteBuffers( 1, &m_EBO );
			delete m_refCount;
		}

		m_VAO = 0;
		m_VBO = 0;
		m_EBO = 0;
		m_refCount = nullptr;
	}
}
