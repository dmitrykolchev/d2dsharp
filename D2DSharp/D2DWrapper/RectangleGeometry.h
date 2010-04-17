/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "Geometry.h"

namespace Managed { namespace Graphics { namespace Direct2D 
{
	public ref class RectangleGeometry: Geometry
	{
	internal:
		RectangleGeometry(ID2D1RectangleGeometry *native): Geometry(native)
		{
		}
	public:
		property Managed::Graphics::Direct2D::RectF Rect
		{
			Managed::Graphics::Direct2D::RectF get()
			{
				Managed::Graphics::Direct2D::RectF rect;
				GetNative()->GetRect((D2D1_RECT_F *)&rect);
				return rect;
			}
		}
	private:
		ID2D1RectangleGeometry *GetNative()
		{
			return (ID2D1RectangleGeometry *)Geometry::GetNative();
		}
	};
}}}