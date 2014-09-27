/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "Brush.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	[StructLayout(LayoutKind::Sequential)]
	public value struct RadialGradientBrushProperties
	{
	private:
		PointF _center;
		PointF _origin;
		FLOAT _radiusX;
		FLOAT _radiusY;
	public:
		RadialGradientBrushProperties(PointF center, PointF origin, FLOAT radiusX, FLOAT radiusY)
		{
			_center = center;
			_origin = origin;
			_radiusX = radiusX;
			_radiusY = radiusY;
		}
	};


	public ref class RadialGradientBrush: Brush
	{
	internal:
		RadialGradientBrush(ID2D1RadialGradientBrush* brush): 
			Brush(brush)
		{
		}
	public:

	};
}}}