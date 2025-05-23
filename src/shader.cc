#include "GLFR/shader.hh"

#include <cstdio>

#include <utility>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x2.hpp>

#include <glm/mat3x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x2.hpp>

#include <glm/mat2x4.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x2.hpp>

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace
{
	const char* ReadFileContent( const char *filePath )
	{
		FILE *fp = std::fopen( filePath, "rb" );
		if( !fp )
		{
			fprintf( stderr, "Failed to open file: %s\n", filePath );
			return nullptr;
		}

		long fileSize;
		char *buffer;

		fseek( fp, 0L, SEEK_END );
		fileSize = ftell( fp );
		rewind( fp );

		buffer = new char[ fileSize + 1 ];
		if( !buffer )
		{
			fclose( fp );
			fprintf( stderr, "Failed to allocate memory for content of: %s\n", filePath );
			return nullptr;
		}

		if( 1 != fread( buffer, fileSize, 1, fp ) )
		{
			fclose( fp );
			delete[] buffer;
			fprintf( stderr, "Failed to read content of: %s\n", filePath );
			return nullptr;
		}

		fclose( fp );
		return buffer;
	}

	GLuint CreateShaderFromSource( const GLenum shaderType, const char *source )
	{
		GLuint shader = glCreateShader( shaderType );
		glShaderSource( shader, 1, &source, nullptr );
		glCompileShader( shader );

		int success;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
		if( !success )
		{
			char infoLog[512];
			glGetShaderInfoLog( shader, 512, nullptr, infoLog );
			fprintf( stderr, "Shader Compilation Error:\n%s\n", infoLog );
			return 0;
		}
		return shader;
	}
}

namespace glfr
{
	Shader::Shader( const Shader &other )
		: m_handle{ other.m_handle }, m_refCount{ other.m_refCount }
	{
		if( m_refCount )
			(*m_refCount)++;
	}

	Shader::Shader( Shader &&other ) noexcept
		: m_handle{ other.m_handle }, m_refCount{ other.m_refCount }
	{
		other.m_handle = 0;
		other.m_refCount = nullptr;
	}

	Shader& Shader::operator=( const Shader &other )
	{
		if( this != &other )
		{
			ReleaseHandle();

			m_handle = other.m_handle;
			m_refCount = other.m_refCount;

			if( m_refCount )
				(*m_refCount)++;
		}

		return *this;
	}

	Shader& Shader::operator=( Shader &&other ) noexcept
	{
		if( this != &other )
		{
			ReleaseHandle();

			m_handle = other.m_handle;
			m_refCount = other.m_refCount;

			other.m_handle = 0;
			other.m_refCount = nullptr;
		}
		
		return *this;
	}

	Shader::~Shader()
	{
		ReleaseHandle();
	}

	void Shader::ReleaseHandle()
	{
		if( m_refCount && --(*m_refCount) == 0 )
		{
			glDeleteProgram( m_handle );
			delete m_refCount;
		}

		m_refCount = nullptr;
		m_handle = 0;
	}

	Shader Shader::FromSources( const char *vertexShaderSource, const char *fragmentShaderSource )
	{
		Shader shader;

		GLuint vertexShader = CreateShaderFromSource( GL_VERTEX_SHADER, vertexShaderSource );
		if( !vertexShader )
		{
			fputs( "Failed to create vertex Shader\n", stderr );
			return shader;
		}

		GLuint fragmentShader = CreateShaderFromSource( GL_FRAGMENT_SHADER, fragmentShaderSource );
		if( !fragmentShader )
		{
			glDeleteShader( vertexShader );
			fputs( "Failed to create fragment Shader\n", stderr );
			return shader;
		}

		shader.m_handle = glCreateProgram( );
		glAttachShader( shader.m_handle, vertexShader );
		glAttachShader( shader.m_handle, fragmentShader );
		glLinkProgram( shader.m_handle );

		int success;
		glGetProgramiv( shader.m_handle, GL_LINK_STATUS, &success );
		if( !success )
		{
			char infoLog[512];
			glGetProgramInfoLog( shader.m_handle, 512, nullptr, infoLog );

			glDeleteShader( vertexShader );
			glDeleteShader( fragmentShader );
			glDeleteProgram( shader.m_handle );
			fprintf( stderr, "Program Linking Error: \n%s\n", infoLog );
			return shader;
		}

		glDeleteShader( vertexShader );
		glDeleteShader( fragmentShader );

		shader.m_refCount = new int{ 1 };

		return shader;

	}

	Shader Shader::FromFiles( const char *vertexShaderPath, const char *fragmentShaderPath )
	{
		const char *pVertexShaderSource = ReadFileContent( vertexShaderPath );
		const char *pFragmentShaderSource = ReadFileContent( fragmentShaderPath );

		Shader shader = std::move( FromSources( pVertexShaderSource, pFragmentShaderSource ) );

		delete[] pVertexShaderSource;
		delete[] pFragmentShaderSource;

		return shader;
	}

	Shader Shader::Default()
	{
		static Shader defaultShader
		{
			std::move( FromSources( 
						"#version 330 core\n"
						"layout ( location = 0 ) in vec3 vertexPos;\n"
						"layout ( location = 1 ) in vec2 uv;"
						"uniform mat4 mvpMatrix;"
						"out vec2 uvCoords;"
						"void main()\n"
						"{\n"
						"	uvCoords = uv;"
						"	gl_Position = mvpMatrix * vec4(vertexPos, 1.0);\n"
						"}\0"

						, //###

						"#version 330 core\n"
						"struct Material\n"
						"{\n"
						"	vec3 diffuseColor;\n"
						"};\n"
						"in vec2 uvCoords;"
						"uniform Material material;"
						"out vec4 fragColor;\n"
						"void main()\n"
						"{\n"
						"	fragColor = vec4(material.diffuseColor, 1.0f);\n"
						"	//fragColor = vec4(uvCoords, 0.0, 1.0);\n"
						"}\n\0"
						) 
						)
		};

		return defaultShader;
	}

	void Shader::Use() const
	{
		glUseProgram( m_handle );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat4 &value ) const 
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat4x3 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniformMatrix4x3fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat4x2 &value ) const 
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniformMatrix4x2fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat3 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniformMatrix3fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat3x4 &value ) const 
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniformMatrix3x4fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat3x2 &value ) const 
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniformMatrix3x2fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat2 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniformMatrix2fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat2x4 &value ) const 
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniformMatrix2x4fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat2x3 &value ) const 
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniformMatrix2x3fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}


	void Shader::SetUniformValue( const char *name, const glm::vec4 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform4fv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::vec3 &value ) const 
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform3fv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::vec2 &value ) const 
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform2fv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const float x, const float y, const float z, const float w ) const 
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform4f( uniformLocation, x, y, z, w );
	}

	void Shader::SetUniformValue( const char *name, const float x, const float y, const float z ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform3f( uniformLocation, x, y, z );
	}

	void Shader::SetUniformValue( const char *name, const float x, const float y ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform2f( uniformLocation, x, y );
	}

	void Shader::SetUniformValue( const char *name, const float x ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform1f( uniformLocation, x );
	}

	void Shader::SetUniformValue( const char *name, const glm::ivec4 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform4iv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::ivec3 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform3iv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::ivec2 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform2iv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const int x, const int y, const int z, const int w ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform4i( uniformLocation, x, y, z, w );
	}

	void Shader::SetUniformValue( const char *name, const int x, const int y, const int z ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform3i( uniformLocation, x, y, z );
	}

	void Shader::SetUniformValue( const char *name, const int x, const int y ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform2i( uniformLocation, x, y );
	}

	void Shader::SetUniformValue( const char *name, const int x ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform1i( uniformLocation, x );
	}

	void Shader::SetUniformValue( const char *name, const glm::uvec4 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform4uiv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::uvec3 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform3uiv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::uvec2 &value ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform2uiv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int w ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform4ui( uniformLocation, x, y, z, w );
	}

	void Shader::SetUniformValue( const char *name, const unsigned int x, const unsigned int y, const unsigned int z ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform3ui( uniformLocation, x, y, z );
	}

	void Shader::SetUniformValue( const char *name, const unsigned int x, const unsigned int y ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform2ui( uniformLocation, x, y );
	}

	void Shader::SetUniformValue( const char *name, const unsigned int x ) const
	{
		GLint uniformLocation = glGetUniformLocation( m_handle, name );
		glUniform1ui( uniformLocation, x );
	}
}
