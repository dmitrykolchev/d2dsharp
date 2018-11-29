/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*
*/
#pragma once

#include "D2DCommon.h"
#include "Geometry.h"

namespace Managed { namespace Graphics { namespace Direct2D 
{
	[System::Security::SuppressUnmanagedCodeSecurity]
	public ref class RoundedRectangleGeometry: Geometry
	{
	internal:
		RoundedRectangleGeometry(ID2D1RoundedRectangleGeometry *native): Geometry(native)
		{
		}
	public:
		property Managed::Graphics::Direct2D::RoundedRect RoundedRect
		{
			Managed::Graphics::Direct2D::RoundedRect get()
			{
				Managed::Graphics::Direct2D::RoundedRect rect;
				GetNative<ID2D1RoundedRectangleGeometry>()->GetRoundedRect((D2D1_ROUNDED_RECT *) &rect);
				return rect;
			}
		}
	};
}}}