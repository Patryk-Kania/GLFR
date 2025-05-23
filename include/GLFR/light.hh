#ifndef GLFR_LIGHT_HH
#define GLFR_LIGHT_HH

#include <glm/vec3.hpp>

#include "color.hh"

namespace glfr
{
	struct Light
	{
		enum EType { POINT_LIGHT = 0, SPOT_LIGHT, DIRECTIONAL_LIGHT };
		EType type;
		
		Color color = Color::White();
		glm::vec3 position;
		glm::vec3 direction;
		float spotAngle = 90;
		float range = 10.0f;
		float intensity = 1.0f;
		bool enabled = true;
	};
}

#endif
