#ifndef GLFR_MATERIAL_HH
#define GLFR_MATERIAL_HH

#include "texture2d.hh"
#include "color.hh"

namespace glfr
{
	struct Material
	{
		Color ambientColor;
		Color diffuseColor;
		Color specularColor;
		Color emissiveColor;
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
