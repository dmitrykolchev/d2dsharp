/*
*
* Authors:
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*
*/
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed {
	namespace Graphics {
		value struct Vector4;

		namespace Direct2D
		{

			[StructLayout(LayoutKind::Sequential)]
			public value struct Color
			{
			internal:
				FLOAT r;
				FLOAT g;
				FLOAT b;
				FLOAT a;
			internal:
				Color(const D2D1_COLOR_F& color)
				{
					r = color.r;
					g = color.g;
					b = color.b;
					a = color.a;
				}
			private:
				Color(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha)
				{
					r = red;
					g = green;
					b = blue;
					a = alpha;
				}
			public:
				[ObsoleteAttribute("Use FromRGB method")]
				static Color FromARGB(int color, FLOAT alpha)
				{
					return Color(
						(float) ((color & 0xFF0000) >> 16) / 255,
						(float) ((color & 0x00FF00) >> 8) / 255,
						(float) (color & 0x0000FF) / 255,
						alpha);
				}
				static Color FromKnown(int color, FLOAT alpha)
				{
					return Color(
						(float) ((color & 0xFF0000) >> 16) / 255,
						(float) ((color & 0x00FF00) >> 8) / 255,
						(float) (color & 0x0000FF) / 255,
						alpha);
				}
				static Color FromRGB(FLOAT red, FLOAT green, FLOAT blue, FLOAT alpha)
				{
					return Color(red, green, blue, alpha);
				}
				static Color FromRGB(FLOAT red, FLOAT green, FLOAT blue)
				{
					return Color(red, green, blue, 1);
				}
				static Color FromRGB(byte r, byte g, byte b, byte a)
				{
					return Color((float) r / 255, (float) g / 255, (float) g / 255, (float) a / 255);
				}
				static Color FromRGB(byte r, byte g, byte b)
				{
					return Color((float) r / 255, (float) g / 255, (float) g / 255, 1);
				}
				[ObsoleteAttribute("Use FromRGB method")]
				static Color FromARGB(FLOAT alpha, FLOAT red, FLOAT green, FLOAT blue)
				{
					return Color(red, green, blue, alpha);
				}

				property FLOAT A
				{
					FLOAT get() { return a; }
				}

				property FLOAT R
				{
					FLOAT get() { return r; }
				}

				property FLOAT G
				{
					FLOAT get() { return g; }
				}

				property FLOAT B
				{
					FLOAT get() { return b; }
				}

				Color AdjustContrast(FLOAT contrast);
				Color AdjustSaturation(FLOAT saturation);
				static Color operator*(Color c1, Color c2);
				static Color Modulate(Color c1, Color c2);

				Vector4 ToSRGB();
				Vector4 ToHSL();
				Vector4 ToHSV();
				Vector4 ToXYZ();
				Vector4 ToYUV();

				static Color FromSRGB(float r, float g, float b, float a);
				static Color FromHSL(float h, float s, float l, float a);
				static Color FromHSV(float h, float s, float v, float a);
				static Color FromXYZ(float x, float y, float z, float a);
				static Color FromYUV(float y, float u, float v, float a);
			};
		}
	}
}