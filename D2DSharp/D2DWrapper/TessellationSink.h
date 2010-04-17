/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "ComWrapper.h"
#include "D2DCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	public ref class TessellationSink: ComWrapper
	{
	internal:
		TessellationSink(ID2D1TessellationSink *native):
			ComWrapper(native)
		{
		}
	public:
		void AddTriangles(array<Triangle>^ triangles)
		{
			pin_ptr<Triangle> p = &triangles[0];
			GetNative()->AddTriangles((D2D1_TRIANGLE *)p, triangles->Length);
		}

		void Close()
		{
			HRESULT hr = GetNative()->Close();
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}

	internal:
		ID2D1TessellationSink *GetNative() new 
		{
			return (ID2D1TessellationSink *)ComWrapper::GetNative();
		}
	};
}}}