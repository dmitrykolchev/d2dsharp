/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "stdafx.h"

#include "PathGeometry.h"

namespace Managed { namespace Graphics { namespace Direct2D 
{
	GeometrySink^ PathGeometry::Open()
	{
		ID2D1GeometrySink *geometrySink;
		
		HRESULT hr = GetNative()->Open(&geometrySink);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew GeometrySink(geometrySink);
	}

	void PathGeometry::Stream(GeometrySink^ geometrySink)
	{
		HRESULT hr = GetNative()->Stream(geometrySink->GetNative());
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}
}}}