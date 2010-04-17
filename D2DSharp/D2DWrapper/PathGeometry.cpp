/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "stdafx.h"

#include "PathGeometry.h"

using namespace Managed::Graphics::Direct2D;

GeometrySink^ PathGeometry::Open()
{
	ID2D1GeometrySink *geometrySink;
		
	ComUtils::CheckResult(GetNative()->Open(&geometrySink));

	return gcnew GeometrySink(geometrySink);
}

void PathGeometry::Stream(GeometrySink^ geometrySink)
{
	ComUtils::CheckResult(GetNative()->Stream(geometrySink->GetNative()));
}

void PathGeometry::Stream(ICustomGeometrySink^ customGeometrySink)
{
	CustomGeometrySink *pSink = new CustomGeometrySink(customGeometrySink);
	try
	{
		ComUtils::CheckResult(GetNative()->Stream(static_cast<ID2D1GeometrySink*>(pSink)));
	}
	finally
	{
		pSink->Release();
	}
}