#pragma once

#include "D2DCommon.h"
#include "Geometry.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class EllipseGeometry: Geometry
	{
	internal:
		EllipseGeometry(ID2D1EllipseGeometry *native): Geometry(native)
		{
		}
	public:
		property DykBits::Graphics::Direct2D::Ellipse Ellipse
		{
			DykBits::Graphics::Direct2D::Ellipse get()
			{
				DykBits::Graphics::Direct2D::Ellipse ellipse;
				GetNative()->GetEllipse((D2D1_ELLIPSE *)&ellipse);
				return ellipse;
			}
		}
	private:
		ID2D1EllipseGeometry *GetNative()
		{
			return (ID2D1EllipseGeometry *)Geometry::GetNative();
		}
	};
}}}