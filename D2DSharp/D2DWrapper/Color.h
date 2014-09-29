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
				[System::ComponentModel::BrowsableAttribute(false)]
				[System::ComponentModel::EditorBrowsableAttribute(System::ComponentModel::EditorBrowsableState::Never)]
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
					return Color((float) r / 255, (float) g / 255, (float) b / 255, (float) a / 255);
				}
				static Color FromRGB(byte r, byte g, byte b)
				{
					return Color((float) r / 255, (float) g / 255, (float) b / 255, 1);
				}
				[ObsoleteAttribute("Use FromRGB method")]
				[System::ComponentModel::BrowsableAttribute(false)]
				[System::ComponentModel::EditorBrowsableAttribute(System::ComponentModel::EditorBrowsableState::Never)]
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
				Color AdjustBrightness(FLOAT brightness);
				Color Invert()
				{
					return Color::FromRGB(1.f - R, 1.f - G, 1.f - B, A);
				}

				static Color operator*(Color c1, Color c2);
				static Color Modulate(Color c1, Color c2);

				Vector4 ToSRGB();
				Vector4 ToHSL();
				Vector4 ToHSV();
				Vector4 ToXYZ();
				Vector4 ToYUV();

				static Color Lerp(Color c1, Color c2, float t);
				static Color FromSRGB(float r, float g, float b, float a);
				static Color FromHSL(float h, float s, float l, float a);
				static Color FromHSV(float h, float s, float v, float a);
				static Color FromXYZ(float x, float y, float z, float a);
				static Color FromYUV(float y, float u, float v, float a);

				static Color Normal(Color a, Color b)
				{
					return b;
				}
				static Color AlphaBlend(Color a, Color b)
				{
					return Color::FromRGB(b.R * b.A + a.R * a.A * (1.f - b.A),
						b.G * b.A - a.G * a.A * (1.f - b.A),
						b.B * b.A - a.B * a.A * (1.f - b.A),
						b.A + a.A * (1.f - b.A));
				}
				static Color Multiply(Color a, Color b)
				{
					return Color::FromRGB(a.R * b.R, a.G * b.G, a.B * b.B, b.A);
				}
				static Color Screen(Color a, Color b)
				{
					return Color::FromRGB(Screen(a.R, b.R), Screen(a.G, b.G), Screen(a.B, b.B), b.A);
				}
				static Color Overlay(Color a, Color b)
				{
					return Color::FromRGB(Overlay(a.R, b.R), Overlay(a.G, b.G), Overlay(a.B, b.B), b.A);
				}
				static Color HardLight(Color a, Color b)
				{
					return Color::FromRGB(HardLight(a.R, b.R), HardLight(a.G, b.G), HardLight(a.B, b.B), b.A);
				}
				static Color SoftLight(Color a, Color b)
				{
					return Color::FromRGB(SoftLight(a.R, b.R), SoftLight(a.G, b.G), SoftLight(a.B, b.B), b.A);
				}
				static Color Darken(Color a, Color b)
				{
					return Color::FromRGB(Math::Min(a.R, b.R), Math::Min(a.G, b.G), Math::Min(a.B, b.B), b.A);
				}
				static Color Lighten(Color a, Color b)
				{
					return Color::FromRGB(Math::Max(a.R, b.R), Math::Max(a.G, b.G), Math::Max(a.B, b.B), b.A);
				}
			private:
				static FLOAT HardLight(FLOAT a, FLOAT b)
				{
					if (b < 0.5f)
						return 2.f * a * b;
					return 1.0f - 2.f * (1.f - a) * (1.f - b);
				}

				static FLOAT SoftLight(FLOAT a, FLOAT b)
				{
					if (b < 0.5f)
						return 2.f * a * b + a * a * (1.f - 2.f * b);
					return (float)(2.f * a * (1.f - b) + Math::Sqrt(a) * (2.f * b - 1.f));
				}

				static FLOAT Screen(FLOAT a, FLOAT b)
				{
					return 1.0f - (1.f - a) * (1.f - b);
				}

				static FLOAT Overlay(FLOAT a, FLOAT b)
				{
					if (a < 0.5f)
						return 2.f * a * b;
					return 1.f - 2.f * (1.f - a) * (1.f - b);
				}

			};
		}
	}
}