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

namespace Managed { namespace Graphics { namespace Direct2D 
{
	[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
	public value struct LinearGradientBrushProperties
	{
	private:
		PointF _startPoint;
		PointF _endPoint;
	public:
		LinearGradientBrushProperties(PointF startPoint, PointF endPoint)
		{
			_startPoint = startPoint;
			_endPoint = endPoint;
		}
	};

	[System::Security::SuppressUnmanagedCodeSecurity]
	public ref class LinearGradientBrush: Brush
	{
	internal:
		LinearGradientBrush(ID2D1LinearGradientBrush* brush): 
			Brush(brush)
		{
		}
	};
}}}