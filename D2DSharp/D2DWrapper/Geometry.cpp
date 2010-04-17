/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "stdafx.h"

#include "Geometry.h"
#include "SimplifiedGeometrySink.h"

namespace Managed { namespace Graphics { namespace Direct2D 
{
	void Geometry::CombineWithGeometry(
			Geometry^ inputGeometry, 
			CombineMode combineMode, 
			Matrix3x2 inputGeometryTransform, 
			FLOAT flatteningTolerance, 
			SimplifiedGeometrySink^ geometrySink)
	{
		HRESULT hr = GetNative()->CombineWithGeometry(
			inputGeometry->GetNative(),
			(D2D1_COMBINE_MODE)combineMode,
			(D2D1_MATRIX_3X2_F *)&inputGeometryTransform,
			flatteningTolerance,
			geometrySink->GetNative());
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	GeometryRelation Geometry::CompareWithGeometry(
			Geometry^ inputGeometry,
			Matrix3x2 inputGeometryTransform, 
			FLOAT flatteningTolerance)
	{
		D2D1_GEOMETRY_RELATION relation;
		HRESULT hr = GetNative()->CompareWithGeometry(
			inputGeometry->GetNative(),
			(D2D1_MATRIX_3X2_F *)&inputGeometryTransform,
			flatteningTolerance,
			&relation);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return (GeometryRelation)relation;
	}
}}}