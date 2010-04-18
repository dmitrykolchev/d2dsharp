/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "Geometry.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	ref class GeometrySink;
	interface class ICustomGeometrySink;

	public ref class PathGeometry: Geometry
	{
	internal:
		PathGeometry(ID2D1PathGeometry *native): 
			Geometry(native)
		{
		}
	public:
		property int FigureCount
		{
			int get()
			{
				UINT32 count;
				ComUtils::CheckResult(GetNative()->GetFigureCount(&count));
				return (int)count;
			}
		}

		property int SegmentCount
		{
			int get()
			{
				UINT32 count;
				ComUtils::CheckResult(GetNative()->GetSegmentCount(&count));
				return (int)count;
			}
		}

		GeometrySink^ Open();
		void Stream(GeometrySink^ geometrySink);
		void Stream(ICustomGeometrySink^ customGeometrySink);

	private:
		ID2D1PathGeometry *GetNative()
		{
			return (ID2D1PathGeometry *)Geometry::GetNative();
		}
	};
}}}