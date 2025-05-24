#include "GLFR/renderer.hh"

#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "GLFR/shader.hh"
#include "GLFR/material.hh"

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

	void Renderer::AddLight( Light light )
	{
		if( m_numOfLights < kMaxNumOfLights )
		{
			m_lights[m_numOfLights++] = light;
		}
	}

	void Renderer::ClearLights()
	{
		m_numOfLights = 0;
	}
	
	void Renderer::DrawMesh( const Mesh &mesh, const glm::mat4 &transform )
	{
		mesh.material.shader.Use();

		glm::mat4 mvpMatrix = m_projectionMatrix * m_viewMatrix * transform;
		glm::mat3 normalMatrix = glm::mat3{ glm::transpose( glm::inverse( transform ) ) };

		mesh.material.shader.SetUniformValue( "mvpMatrix", mvpMatrix );
		mesh.material.shader.SetUniformValue( "modelMatrix", transform );
		mesh.material.shader.SetUniformValue( "normalMatrix", normalMatrix );
		mesh.material.shader.SetUniformValue( "cameraPos", m_camera.position );

		mesh.material.shader.SetUniformValue( "globalAmbient", glm::vec3{ .2f } );

		mesh.material.shader.SetUniformValue( "material.isAffectedByLight",
						      mesh.material.isAffectedByLight );

		mesh.material.shader.SetUniformValue( "material.ambientColor",
						      mesh.material.ambientColor.ToVec3() );
		mesh.material.shader.SetUniformValue( "material.diffuseColor",
						      mesh.material.diffuseColor.ToVec3() );
		mesh.material.shader.SetUniformValue( "material.specularColor",
						      mesh.material.specularColor.ToVec3() );
		mesh.material.shader.SetUniformValue( "material.emissiveColor",
						      mesh.material.emissiveColor.ToVec3() );
		mesh.material.shader.SetUniformValue( "material.opacity",
						      mesh.material.opacity );
		mesh.material.shader.SetUniformValue( "material.specularPower",
						      mesh.material.specularPower );
		mesh.material.shader.SetUniformValue( "material.alphaThreshold",
						      mesh.material.alphaThreshold );

		bool hasAmbientTexture = mesh.material.ambientTexture.IsValid();
		mesh.material.shader.SetUniformValue( "material.hasAmbientTexture", hasAmbientTexture );
		if( hasAmbientTexture )
		{
			mesh.material.shader.SetUniformValue( "material.ambientTexture", 0 );
			mesh.material.ambientTexture.Bind( 0 );
		}

		bool hasDiffuseTexture = mesh.material.diffuseTexture.IsValid();
		mesh.material.shader.SetUniformValue( "material.hasDiffuseTexture", hasDiffuseTexture );
		if( hasDiffuseTexture )
		{
			mesh.material.shader.SetUniformValue( "material.diffuseTexture", 1 );
			mesh.material.ambientTexture.Bind( 1 );
		}

		bool hasSpecularTexture = mesh.material.specularTexture.IsValid();
		mesh.material.shader.SetUniformValue( "material.hasSpecularTexture", hasSpecularTexture );
		if( hasSpecularTexture )
		{
			mesh.material.shader.SetUniformValue( "material.specularTexture", 2 );
			mesh.material.specularTexture.Bind( 2 );
		}

		bool hasEmissiveTexture = mesh.material.emissiveTexture.IsValid();
		mesh.material.shader.SetUniformValue( "material.hasEmissiveTexture", hasEmissiveTexture );
		if( hasEmissiveTexture )
		{
			mesh.material.shader.SetUniformValue( "material.emissiveTexture", 3 );
			mesh.material.specularTexture.Bind( 3 );
		}

		bool hasSpecularPowerTexture = mesh.material.specularPowerTexture.IsValid();
		mesh.material.shader.SetUniformValue( "material.hasSpecularPowerTexture", hasSpecularPowerTexture );
		if( hasSpecularPowerTexture )
		{
			mesh.material.shader.SetUniformValue( "material.specularPowerTexture", 4 );
			mesh.material.specularTexture.Bind( 4 );
		}

		bool hasOpacityTexture = mesh.material.opacityTexture.IsValid();
		mesh.material.shader.SetUniformValue( "material.hasOpacityTexture", hasOpacityTexture );
		if( hasOpacityTexture )
		{
			mesh.material.shader.SetUniformValue( "material.opacityTexture", 5 );
			mesh.material.opacityTexture.Bind( 5 );
		}

		bool hasNormalTexture = mesh.material.normalTexture.IsValid();
		mesh.material.shader.SetUniformValue( "material.hasNormalTexture", hasNormalTexture );
		if( hasOpacityTexture )
		{
			mesh.material.shader.SetUniformValue( "material.normalTexture", 6 );
			mesh.material.opacityTexture.Bind( 6 );
		}

		mesh.material.shader.SetUniformValue( "numOfLights", m_numOfLights );
		for( int i = 0; i < m_numOfLights; i++)
		{
			std::string light = "lights[" + std::to_string( i ) + "].";

			mesh.material.shader.SetUniformValue( (light + "type").c_str(), m_lights[i].type );
			mesh.material.shader.SetUniformValue( (light + "color").c_str(), m_lights[i].color.ToVec3() );
			mesh.material.shader.SetUniformValue( (light + "position").c_str(), m_lights[i].position );
			mesh.material.shader.SetUniformValue( (light + "direction").c_str(), m_lights[i].direction );
			mesh.material.shader.SetUniformValue( (light + "spotAngle").c_str(), m_lights[i].spotAngle );
			mesh.material.shader.SetUniformValue( (light + "range").c_str(), m_lights[i].range );
			mesh.material.shader.SetUniformValue( (light + "intensity").c_str(), m_lights[i].intensity );
			mesh.material.shader.SetUniformValue( (light + "enabled").c_str(), m_lights[i].enabled );
		}

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
