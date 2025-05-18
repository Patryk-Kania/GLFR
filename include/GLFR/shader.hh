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
		bool LoadFromSources( const char *vertexShaderSource, const char *fragmentShaderSource );
		bool LoadFromFiles( const char *vertexShaderPath, const char *fragmentShaderPath );
		void Use();

		void SetUniformValue( const char *name, const glm::mat4 &value ); 
		void SetUniformValue( const char *name, const glm::mat4x3 &value ); 
		void SetUniformValue( const char *name, const glm::mat4x2 &value ); 

		void SetUniformValue( const char *name, const glm::mat3 &value ); 
		void SetUniformValue( const char *name, const glm::mat3x4 &value ); 
		void SetUniformValue( const char *name, const glm::mat3x2 &value ); 

		void SetUniformValue( const char *name, const glm::mat2 &value ); 
		void SetUniformValue( const char *name, const glm::mat2x4 &value ); 
		void SetUniformValue( const char *name, const glm::mat2x3 &value ); 


		void SetUniformValue( const char *name, const glm::vec4 &value ); 
		void SetUniformValue( const char *name, const glm::vec3 &value ); 
		void SetUniformValue( const char *name, const glm::vec2 &value ); 

		void SetUniformValue( const char *name, const float x, const float y, const float z, const float w ); 
		void SetUniformValue( const char *name, const float x, const float y, const float z ); 
		void SetUniformValue( const char *name, const float x, const float y ); 
		void SetUniformValue( const char *name, const float x ); 
	private:
		GLuint m_shaderProgram;
	};
}

#endif
