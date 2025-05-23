#ifndef GLFR_SHADER_HH
#define GLFR_SHADER_HH

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

namespace glfr
{
	class Shader
	{
	public:
		Shader() : m_handle{ 0 }, m_refCount{ nullptr } {}
		Shader( const Shader &other );
		Shader( Shader &&other ) noexcept;

		Shader& operator=( const Shader &other );
		Shader& operator=( Shader &&other ) noexcept;

		~Shader();

		void ReleaseHandle();

		static Shader FromSources( const char *vertexShaderSource, const char *fragmentShaderSource );
		static Shader FromFiles( const char *vertexShaderPath, const char *fragmentShaderPath );
		static Shader Default();

		void Use() const;

		void SetUniformValue( const char *name, const glm::mat4 &value ) const; 
		void SetUniformValue( const char *name, const glm::mat4x3 &value ) const; 
		void SetUniformValue( const char *name, const glm::mat4x2 &value ) const; 

		void SetUniformValue( const char *name, const glm::mat3 &value ) const; 
		void SetUniformValue( const char *name, const glm::mat3x4 &value ) const; 
		void SetUniformValue( const char *name, const glm::mat3x2 &value ) const; 

		void SetUniformValue( const char *name, const glm::mat2 &value ) const; 
		void SetUniformValue( const char *name, const glm::mat2x4 &value ) const; 
		void SetUniformValue( const char *name, const glm::mat2x3 &value ) const; 


		void SetUniformValue( const char *name, const glm::vec4 &value ) const; 
		void SetUniformValue( const char *name, const glm::vec3 &value ) const; 
		void SetUniformValue( const char *name, const glm::vec2 &value ) const; 

		void SetUniformValue( const char *name, const float x, const float y, const float z, const float w ) const; 
		void SetUniformValue( const char *name, const float x, const float y, const float z ) const; 
		void SetUniformValue( const char *name, const float x, const float y ) const; 
		void SetUniformValue( const char *name, const float x ) const; 

		void SetUniformValue( const char *name, const glm::ivec4 &value ) const; 
		void SetUniformValue( const char *name, const glm::ivec3 &value ) const; 
		void SetUniformValue( const char *name, const glm::ivec2 &value ) const; 

		void SetUniformValue( const char *name, const int x, const int y, const int z, const int w ) const; 
		void SetUniformValue( const char *name, const int x, const int y, const int z ) const; 
		void SetUniformValue( const char *name, const int x, const int y ) const; 
		void SetUniformValue( const char *name, const int x ) const; 

		void SetUniformValue( const char *name, const glm::uvec4 &value ) const; 
		void SetUniformValue( const char *name, const glm::uvec3 &value ) const; 
		void SetUniformValue( const char *name, const glm::uvec2 &value ) const; 

		void SetUniformValue( const char *name, const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int w ) const; 
		void SetUniformValue( const char *name, const unsigned int x, const unsigned int y, const unsigned int z ) const; 
		void SetUniformValue( const char *name, const unsigned int x, const unsigned int y ) const; 
		void SetUniformValue( const char *name, const unsigned int x ) const; 

	private:
		GLuint m_handle;
		int *m_refCount;
	};
}

#endif
