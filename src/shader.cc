#include "GLFR/shader.hh"

#include <cstdio>

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
	bool Shader::LoadFromSources( const char *vertexShaderSource, const char *fragmentShaderSource )
	{
		GLuint vertexShader = CreateShaderFromSource( GL_VERTEX_SHADER, vertexShaderSource );
		if( !vertexShader )
		{
			fputs( "Failed to create vertex Shader", stderr );
			return false;
		}

		GLuint fragmentShader = CreateShaderFromSource( GL_FRAGMENT_SHADER, fragmentShaderSource );
		if( !fragmentShader )
		{
			glDeleteShader( vertexShader );
			fputs( "Failed to create fragment Shader", stderr );
			return false;
		}

		m_shaderProgram = glCreateProgram( );
		glAttachShader( m_shaderProgram, vertexShader );
		glAttachShader( m_shaderProgram, fragmentShader );
		glLinkProgram( m_shaderProgram );

		int success;
		glGetProgramiv( m_shaderProgram, GL_LINK_STATUS, &success );
		if( !success )
		{
			char infoLog[512];
			glGetProgramInfoLog( m_shaderProgram, 512, nullptr, infoLog );

			glDeleteShader( vertexShader );
			glDeleteShader( fragmentShader );
			glDeleteProgram( m_shaderProgram );
			fprintf( stderr, "Program Linking Error: \n%s\n", infoLog );
			return false;
		}

		glDeleteShader( vertexShader );
		glDeleteShader( fragmentShader );
		return true;

	}

	bool Shader::LoadFromFiles( const char *vertexShaderPath, const char *fragmentShaderPath )
	{
		const char *pVertexShaderSource = ReadFileContent( vertexShaderPath );
		const char *pFragmentShaderSource = ReadFileContent( fragmentShaderPath );

		bool success = LoadFromSources( pVertexShaderSource, pFragmentShaderSource );

		delete[] pVertexShaderSource;
		delete[] pFragmentShaderSource;

		return success;
	}

	void Shader::Use( )
	{
		glUseProgram( m_shaderProgram );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat4 &value ) 
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat4x3 &value )
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniformMatrix4x3fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat4x2 &value ) 
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniformMatrix4x2fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat3 &value )
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniformMatrix3fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat3x4 &value ) 
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniformMatrix3x4fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat3x2 &value ) 
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniformMatrix3x2fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat2 &value )
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniformMatrix2fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat2x4 &value ) 
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniformMatrix2x4fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::mat2x3 &value ) 
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniformMatrix2x3fv( uniformLocation, 1, GL_FALSE, &value[0][0] );
	}


	void Shader::SetUniformValue( const char *name, const glm::vec4 &value )
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniform4fv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::vec3 &value ) 
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniform3fv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const glm::vec2 &value ) 
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniform2fv( uniformLocation, 1, &value[0] );
	}

	void Shader::SetUniformValue( const char *name, const float x, const float y, const float z, const float w ) 
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniform4f( uniformLocation, x, y, z, w );
	}

	void Shader::SetUniformValue( const char *name, const float x, const float y, const float z )
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniform3f( uniformLocation, x, y, z );
	}

	void Shader::SetUniformValue( const char *name, const float x, const float y )
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniform2f( uniformLocation, x, y );
	}

	void Shader::SetUniformValue( const char *name, const float x )
	{
		GLint uniformLocation = glGetUniformLocation( m_shaderProgram, name );
		glUniform1f( uniformLocation, x );
	}
}
