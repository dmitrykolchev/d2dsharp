#pragma once

#include "D2DCommon.h"
#include "Geometry.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class GeometryGroup: Geometry
	{
	internal:
		GeometryGroup(ID2D1GeometryGroup *native): 
			Geometry(native)
		{
		}
	public:
	private:
		ID2D1GeometryGroup *GetNative() new 
		{
			return (ID2D1GeometryGroup *)Geometry::GetNative();
		}
	};
}}}