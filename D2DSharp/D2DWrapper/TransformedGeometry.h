#pragma once

#include "D2DCommon.h"
#include "Geometry.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
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
				GetNative()->GetSourceGeometry(&geometry);
				return gcnew Geometry(geometry);
			}
		}

		property Matrix3x2 Transform
		{
			Matrix3x2 get()
			{
				Matrix3x2 transform;
				GetNative()->GetTransform((D2D1_MATRIX_3X2_F *)&transform);
				return transform;
			}
		}

	private:
		ID2D1TransformedGeometry *GetNative()
		{
			return (ID2D1TransformedGeometry *)Geometry::GetNative();
		}
	};
}}}