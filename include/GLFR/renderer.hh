#ifndef GLFR_RENDERER_HH
#define GLFR_RENDERER_HH

#include <map>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "mesh.hh"
#include "shader.hh"
#include "material.hh"
#include "light.hh"

namespace glfr
{
	class Renderer
	{
	public:
		static const int kMaxNumOfLights = 10;
		void Init( const int viewportWidth, const int viewportHeight );

		void ClearColor( const int r, const int g, const int b );
		void ClearColor( const int c );
		void ClearDepth();

		void SetCameraPosition( const glm::vec3 &newPosition );
		void TranslateCamera( const glm::vec3 &translation );
		void SetCameraRotation( const glm::vec3 &newRotation );
		void RotateCamera( const glm::vec3 &rotation );
		void SetCameraFOV( const float fov );
		void SetCameraClipDistance( const float near, const float far );

		void AddLight( Light light );
		void ClearLights();

		void DrawMesh( const Mesh &mesh, const Material &material, const glm::mat4 &transform );

	private:
		struct
		{
			glm::vec3 position, rotation;
			float FOV, aspectRatio;
			float nearClipPlane, farClipPlane;
		} m_camera;

		glm::mat4 m_viewMatrix, m_projectionMatrix;
		int m_numOfLights = 0;
		Light m_lights[kMaxNumOfLights];

		void CalculateViewMatrix();
		void CalculateProjectionMatrix();

	};
}

#endif
