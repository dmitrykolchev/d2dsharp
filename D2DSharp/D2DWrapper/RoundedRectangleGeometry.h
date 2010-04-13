#pragma once

#include "D2DCommon.h"
#include "Geometry.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class RoundedRectangleGeometry: Geometry
	{
	internal:
		RoundedRectangleGeometry(ID2D1RoundedRectangleGeometry *native): Geometry(native)
		{
		}
	public:
		property DykBits::Graphics::Direct2D::RoundedRect RoundedRect
		{
			DykBits::Graphics::Direct2D::RoundedRect get()
			{
				DykBits::Graphics::Direct2D::RoundedRect rect;
				GetNative()->GetRoundedRect((D2D1_ROUNDED_RECT *)&rect);
				return rect;
			}
		}
	private:
		ID2D1RoundedRectangleGeometry *GetNative()
		{
			return (ID2D1RoundedRectangleGeometry *)Geometry::GetNative();
		}
	};
}}}