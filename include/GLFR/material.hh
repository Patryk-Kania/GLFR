#ifndef GLFR_MATERIAL_HH
#define GLFR_MATERIAL_HH

#include <glm/vec3.hpp>

#include "texture2d.hh"

namespace glfr
{
	struct Material
	{
		glm::vec3 ambientColor;
		glm::vec3 diffuseColor;
		glm::vec3 specularColor;
		glm::vec3 emissiveColor;
		float opacity;
		float specularPower;
		float alphaThreshold;

		Texture2D ambientTexture;
		Texture2D diffuseTexture;
		Texture2D specularTexture;
		Texture2D emissiveTexture;
		Texture2D specularPowerTexture;
		Texture2D opacityTexture;
		Texture2D normalTexture;
	};
}

#endif
