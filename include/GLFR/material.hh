#ifndef GLFR_MATERIAL_HH
#define GLFR_MATERIAL_HH

#include "texture2d.hh"
#include "color.hh"
#include "shader.hh"

namespace glfr
{
	struct Material
	{
		Shader shader{ Shader::Default() };

		bool isAffectedByLight = true;

		Color ambientColor = Color::White();
		Color diffuseColor = Color::White();
		Color specularColor = Color::White();
		Color emissiveColor;
		float opacity = 1.0f;
		float specularPower = 32.0f;
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
