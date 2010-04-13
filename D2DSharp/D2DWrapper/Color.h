#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	[StructLayout(LayoutKind::Sequential)]
	public value struct Color
	{
	private:
	    FLOAT _red;
	    FLOAT _green;
	    FLOAT _blue;
	    FLOAT _alpha;
	internal:
		Color(const D2D1_COLOR_F& color)
		{
			_red = color.r;
			_green = color.g;
			_blue = color.b;
			_alpha = color.a;
		}
	private:
		Color(FLOAT red, FLOAT green, FLOAT blue)
		{
			_red = red;
			_green = green;
			_blue = blue;
			_alpha = 1;
		}

		Color(FLOAT alpha, FLOAT red, FLOAT green, FLOAT blue)
		{
			_red = red;
			_green = green;
			_blue = blue;
			_alpha = alpha;
		}
	public:
		static Color FromRGB(FLOAT red, FLOAT green, FLOAT blue)
		{
			return Color(red, green, blue);
		}

		static Color FromARGB(FLOAT alpha, FLOAT red, FLOAT green, FLOAT blue)
		{
			return Color(alpha, red, green, blue);
		}

		property FLOAT A 
		{ 
			FLOAT get() { return _alpha; }
		}

		property FLOAT R
		{
			FLOAT get() { return _red; }
		}

		property FLOAT G
		{
			FLOAT get() { return _green; }
		}

		property FLOAT B
		{
			FLOAT get() { return _blue; }
		}
	};
}}}