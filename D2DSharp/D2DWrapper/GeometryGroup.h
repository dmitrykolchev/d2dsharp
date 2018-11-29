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
	[System::Security::SuppressUnmanagedCodeSecurity]
	public ref class GeometryGroup: Geometry
	{
	internal:
		GeometryGroup(ID2D1GeometryGroup *native): 
			Geometry(native)
		{
		}
	public:
	};
}}}