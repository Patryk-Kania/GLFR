#ifndef GLFR_RENDERER_HH
#define GLFR_RENDERER_HH

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "mesh.hh"
#include "shader.hh"

namespace glfr
{
	class Renderer
	{
	public:
		void Init(const int viewportWidth, const int viewportHeight);

		void ClearColor(const int r, const int g, const int b);
		void ClearColor(const int c);
		void ClearDepth();

		void SetCameraPosition(glm::vec3 newPosition);
		void TranslateCamera(glm::vec3 translation);
		void SetCameraRotation(glm::vec3 newRotation);
		void RotateCamera(glm::vec3 rotation);
		void SetCameraFOV(float fov);
		void SetCameraClipDistance(float near, float far);

		void DrawMesh(Mesh &mesh, glm::mat4 transform);

	private:
		struct
		{
			glm::vec3 position, rotation;
			float FOV, aspectRatio;
			float nearClipPlane, farClipPlane;
		} m_camera;

		Shader m_defaultShader;

		glm::mat4 m_viewMatrix, m_projectionMatrix;

		void CalculateViewMatrix();
		void CalculateProjectionMatrix();

	};
}

#endif
