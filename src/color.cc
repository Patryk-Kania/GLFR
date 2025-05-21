#include "GLFR/color.hh"

#include <glm/vec3.hpp>

namespace glfr
{
	Color Color::FromRGBA( const int r, const int g, const int b, const int a )
	{
		Color c;
		c.m_value = glm::vec4{ r / 255.f, g / 255.f, b / 255.f, a / 255.f};
		return c;
	}

	Color Color::FromRGB( const int r, const int g, const int b )
	{
		return FromRGBA( r, g, b, 255 );
	}

	Color Color::FromHSLA( const int h, const float s, const float l, const int a )
	{
		float r, g, b;

		auto hueToRGB = [](float p, float q, float t) -> float
		{
			if (t < 0.0f) t += 1.0f;
			if (t > 1.0f) t -= 1.0f;
			if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
			if (t < 1.0f / 2.0f) return q;
			if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
			return p;
		};

		if (s == 0.0f)
		{
			r = g = b = l;
		}
		else
		{
			float q = (l < 0.5f) ? (l * (1.0f + s)) : (l + s - l * s);
			float p = 2.0f * l - q;
			r = hueToRGB(p, q, h + 1.0f / 3.0f);
			g = hueToRGB(p, q, h);
			b = hueToRGB(p, q, h - 1.0f / 3.0f);
		}

		Color c;
		c.m_value = glm::vec4{ r, g, b, a };
		return c;
	}

	Color Color::FromHSL( const int h, const float s, const float l )
	{
		return FromHSLA( h, s, l, 255 );
	}

}
