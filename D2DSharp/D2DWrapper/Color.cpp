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
		}
	}
}

