#include "GLFR/mesh.hh"

#include <GL/glew.h>

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
	}

	Mesh Mesh::NewQuad()
	{

		GLfloat vertices[] = 
		{
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		GLfloat UVs[] =
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};

		GLfloat normals[] =
		{
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f
		};

		GLuint triangles[] = 
		{
			0, 1, 3,
			1, 2, 3
		};

		return Mesh( 4, vertices, UVs, normals, 2, triangles );

	}

	Mesh Mesh::NewCube()
	{
		GLfloat vertices[] = 
		{
			// Front face
			-0.5f, -0.5f,  0.5f, // 0
			0.5f, -0.5f,  0.5f, // 1
			0.5f,  0.5f,  0.5f, // 2
			-0.5f,  0.5f,  0.5f, // 3

			// Back face
			0.5f, -0.5f, -0.5f, // 4
			-0.5f, -0.5f, -0.5f, // 5
			-0.5f,  0.5f, -0.5f, // 6
			0.5f,  0.5f, -0.5f, // 7

			// Left face
			-0.5f, -0.5f, -0.5f, // 8
			-0.5f, -0.5f,  0.5f, // 9
			-0.5f,  0.5f,  0.5f, //10
			-0.5f,  0.5f, -0.5f, //11

			// Right face
			0.5f, -0.5f,  0.5f, //12
			0.5f, -0.5f, -0.5f, //13
			0.5f,  0.5f, -0.5f, //14
			0.5f,  0.5f,  0.5f, //15

			// Top face
			-0.5f,  0.5f,  0.5f, //16
			0.5f,  0.5f,  0.5f, //17
			0.5f,  0.5f, -0.5f, //18
			-0.5f,  0.5f, -0.5f, //19

			// Bottom face
			-0.5f, -0.5f, -0.5f, //20
			0.5f, -0.5f, -0.5f, //21
			0.5f, -0.5f,  0.5f, //22
			-0.5f, -0.5f,  0.5f  //23
		};

		GLfloat UVs[] = 
		{
			// Front
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Back
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Left
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Right
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Top
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Bottom
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};

		GLfloat normals[] = {
			// Front face (0, 0, 1)
			0.0f,  0.0f,  1.0f,
			0.0f,  0.0f,  1.0f,
			0.0f,  0.0f,  1.0f,
			0.0f,  0.0f,  1.0f,

			// Back face (0, 0, -1)
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,

			// Left face (-1, 0, 0)
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,

			// Right face (1, 0, 0)
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,

			// Top face (0, 1, 0)
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,

			// Bottom face (0, -1, 0)
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f
		};

		GLuint triangles[] = 
		{
			// Front face
			0, 1, 2,
			2, 3, 0,

			// Back face
			4, 5, 6,
			6, 7, 4,

			// Left face
			8, 9,10,
			10,11, 8,

			// Right face
			12,13,14,
			14,15,12,

			// Top face
			16,17,18,
			18,19,16,

			// Bottom face
			20,21,22,
			22,23,20
		};
		return Mesh( 24, vertices, UVs, normals, 12, triangles );

	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays( 1, &m_VAO );
		glDeleteBuffers( 1, &m_VBO );
		glDeleteBuffers( 1, &m_EBO );
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
