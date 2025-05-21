#include "GLFR/renderer.hh"

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "GLFR/shader.hh"
#include "GLFR/material.hh"

const char *vertexShaderSource = 
"#version 330 core\n"
"layout ( location = 0 ) in vec3 vertexPos;\n"
"layout ( location = 1 ) in vec2 uv;"
"uniform mat4 mvpMatrix;"
"out vec2 uvCoords;"
"void main()\n"
"{\n"
"	uvCoords = uv;"
"	gl_Position = mvpMatrix * vec4(vertexPos, 1.0);\n"
"}\0";

const char *fragmentShaderSource = 
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
"}\n\0";

namespace glfr
{
	void Renderer::Init( const int viewportWidth, const int viewportHeight )
	{
		glViewport( 0, 0, viewportWidth, viewportHeight );
		glEnable( GL_DEPTH_TEST );

		m_camera.position = glm::vec3 { 0.f, 0.f, 0.f };
		m_camera.rotation = glm::vec3 { 0.f, 0.f, 0.f };
		m_camera.FOV = 60;
		m_camera.aspectRatio = float( viewportWidth ) / float( viewportHeight );
		m_camera.nearClipPlane = 0.01f;
		m_camera.farClipPlane = 100.f;

		CalculateViewMatrix();
		CalculateProjectionMatrix();

		m_defaultShader.LoadFromSources( vertexShaderSource, fragmentShaderSource );
	}

	void Renderer::ClearColor( const int r, const int g, const int b )
	{
		glClearColor( r / 255.f, g / 255.f, b / 255.f, 1.f );	
		glClear( GL_COLOR_BUFFER_BIT );
	}

	void Renderer::ClearColor( const int c )
	{
		ClearColor( c, c, c );
	}

	void Renderer::ClearDepth()
	{
		glClear( GL_DEPTH_BUFFER_BIT );
	}

	void Renderer::SetCameraPosition( const glm::vec3 &newPosition )
	{
		m_camera.position = newPosition;
		CalculateViewMatrix();
	}

	void Renderer::TranslateCamera( const glm::vec3 &translation )
	{
		m_camera.position += translation;
		CalculateViewMatrix();
	}

	void Renderer::SetCameraRotation( const glm::vec3 &newRotation )
	{
		m_camera.rotation = newRotation;
		CalculateViewMatrix();
	}

	void Renderer::RotateCamera( const glm::vec3 &rotation )
	{
		m_camera.rotation += rotation;
		CalculateViewMatrix();
	}

	void Renderer::SetCameraFOV( const float fov )
	{
		m_camera.FOV = fov;
		CalculateProjectionMatrix();
	}

	void Renderer::SetCameraClipDistance( const float near, const float far )
	{
		m_camera.nearClipPlane = near;
		m_camera.farClipPlane = far;
		CalculateProjectionMatrix();
	}
	
	void Renderer::DrawMesh( const Mesh &mesh, const glm::mat4 &transform )
	{
		m_defaultShader.Use();

		glm::mat4 mvpMatrix = m_projectionMatrix * m_viewMatrix * transform;

		m_defaultShader.SetUniformValue( "mvpMatrix", mvpMatrix );
		m_defaultShader.SetUniformValue( "material.diffuseColor", mesh.material.diffuseColor );

		glBindVertexArray( mesh.GetVAO() );
		glDrawElements( GL_TRIANGLES, mesh.GetNumOfTriangles() * 3, GL_UNSIGNED_INT, nullptr );
	}


	void Renderer::CalculateViewMatrix()
	{
		m_viewMatrix = glm::mat4( 1.0f );
		m_viewMatrix = glm::translate( m_viewMatrix, m_camera.position );
		m_viewMatrix = glm::rotate( m_viewMatrix, glm::radians( m_camera.rotation.x ), glm::vec3{ 1.f,0.f,0.f } );
		m_viewMatrix = glm::rotate( m_viewMatrix, glm::radians( m_camera.rotation.y ), glm::vec3{ 0.f,1.f,0.f } );
		m_viewMatrix = glm::rotate( m_viewMatrix, glm::radians( m_camera.rotation.z ), glm::vec3{ 0.f,0.f,1.f } );
		m_viewMatrix = glm::inverse( m_viewMatrix );
	}

	void Renderer::CalculateProjectionMatrix()
	{
		m_projectionMatrix = glm::perspective( glm::radians( m_camera.FOV ), m_camera.aspectRatio,
						      m_camera.nearClipPlane, m_camera.farClipPlane );
	}
}
