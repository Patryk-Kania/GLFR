#ifndef GLFR_COLOR_HH
#define GLFR_COLOR_HH

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace glfr
{
	class Color
	{
	public:
		Color() : m_value{ 0., 0., 0., 1.f } {}

		static Color FromRGBA( const int r, const int g, const int b, const int a );
		static Color FromRGB( const int r, const int g, const int b );
		static Color FromHSLA( const int h, const float s, const float l, const int a );
		static Color FromHSL( const int h, const float s, const float l );

		glm::vec3 ToVec3() const { return glm::vec3{ m_value }; };
		glm::vec4 ToVec4() const { return m_value; };

		static Color Red() { return FromRGB( 255, 0, 0 ); }
		static Color Green() { return FromRGB( 0, 255, 0 ); }
		static Color Blue() { return FromRGB( 0, 0, 255 ); }

		static Color White() { return FromRGB( 255, 255, 255 ); }
		static Color Black() { return FromRGB( 0, 0, 0 ); }

		static Color LightGray() { return FromRGB( 83, 83, 83 ); }
		static Color DarkGray() { return FromRGB( 169, 169, 169 ); }

		static Color Yellow() { return FromRGB( 255, 255, 0 ); }
		static Color Magenta() { return FromRGB( 255, 0, 255 ); }
		static Color Cyan() { return FromRGB( 0, 255, 255 ); }

		static Color Transparent() { return FromRGBA( 0, 0, 0, 0 ); }
	private:
		glm::vec4 m_value;
	};
}

#endif
