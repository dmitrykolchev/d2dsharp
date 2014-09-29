#include "Stdafx.h"
#include "XMath.h"
#include "Color.h"

namespace Managed {
	namespace Graphics {
		namespace Direct2D {

			Color Color::AdjustContrast(FLOAT contrast)
			{
				return (Color) XMath::ColorAdjustContrast(Vector4(*this), contrast);
			}
			Color Color::AdjustSaturation(FLOAT saturation)
			{
				return (Color) XMath::ColorAdjustSaturation(Vector4(*this), saturation);
			}
			Color Color::AdjustBrightness(FLOAT brightness)
			{
				Vector4 hsl = ToHSL();
				return FromHSL(hsl.X, hsl.Y, hsl.Z * brightness, hsl.W);
			}
			Color Color::Modulate(Color c1, Color c2)
			{
				return (Color) XMath::ColorModulate(Vector4(c1), Vector4(c2));
			}
			Color Color::operator*(Color c1, Color c2)
			{
				return (Color) XMath::ColorModulate(Vector4(c1), Vector4(c2));
			}

			Vector4 Color::ToSRGB()
			{
				return XMath::ColorRgbToSrgb(Vector4(*this));
			}

			Vector4 Color::ToHSL()
			{
				return XMath::ColorRgbToHsl(Vector4(*this));
			}

			Vector4 Color::ToHSV()
			{
				return XMath::ColorRgbToHsv(Vector4(*this));
			}

			Vector4 Color::ToXYZ()
			{
				return XMath::ColorRgbToXyz(Vector4(*this));
			}

			Vector4 Color::ToYUV()
			{
				return XMath::ColorRgbToYuv(Vector4(*this));
			}

			Color Color::FromSRGB(float r, float g, float b, float a)
			{
				return (Color) XMath::ColorSrgbToRgb(Vector4(r, g, b, a));
			}
			Color Color::FromHSL(float h, float s, float l, float a)
			{
				return (Color) XMath::ColorSrgbToRgb(Vector4(h, s, l, a));
			}
			Color Color::FromHSV(float h, float s, float v, float a)
			{
				return (Color) XMath::ColorSrgbToRgb(Vector4(h, s, v, a));
			}
			Color Color::FromXYZ(float x, float y, float z, float a)
			{
				return (Color) XMath::ColorSrgbToRgb(Vector4(x, y, z, a));
			}
			Color Color::FromYUV(float y, float u, float v, float a)
			{
				return (Color) XMath::ColorSrgbToRgb(Vector4(y, u, v, a));
			}

			Color Color::Lerp(Color c1, Color c2, float t)
			{
				return Color::FromRGB(
					c1.R + (c2.R - c1.R) * t,
					c1.G + (c2.G - c1.G) * t,
					c1.B + (c2.B - c1.B) * t,
					c1.A + (c2.A - c1.A) * t
					);
			}

		}
	}
}

