#pragma once

#include "Color.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class Colors sealed
	{
	private:
		Colors()
		{
		}
	public:
		initonly static Color White = Color::FromRGB(1, 1, 1);
		initonly static Color Gray = Color::FromRGB(0.5f, 0.5f, 0.5f);
		initonly static Color Black = Color::FromRGB(0, 0, 0);
		initonly static Color Red = Color::FromRGB(1, 0, 0);
		initonly static Color Green = Color::FromRGB(0, 1, 0);
		initonly static Color Blue = Color::FromRGB(0, 0, 1);
		initonly static Color Cyan = Color::FromRGB(0, 1, 1);
		initonly static Color Magenta = Color::FromRGB(1, 0, 1);
		initonly static Color Yellow = Color::FromRGB(1, 1, 0);
	};
}}}