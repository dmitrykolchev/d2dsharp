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
	public ref class TransformedGeometry: Geometry
	{
	internal:
		TransformedGeometry(ID2D1TransformedGeometry *native): Geometry(native)
		{
		}
	public:
		property Geometry^ SourceGeometry
		{
			Geometry^ get()
			{
				ID2D1Geometry *geometry;
				GetNative<ID2D1TransformedGeometry>()->GetSourceGeometry(&geometry);
				return gcnew Geometry(geometry);
			}
		}

		property Matrix3x2 Transform
		{
			Matrix3x2 get()
			{
				Matrix3x2 transform;
				GetNative<ID2D1TransformedGeometry>()->GetTransform((D2D1_MATRIX_3X2_F *) &transform);
				return transform;
			}
		}
	};
}}}