#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"
#include "TessellationSink.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class Mesh: D2DResource
	{
	internal:
		Mesh(ID2D1Mesh *native): 
			D2DResource(native)
		{
		}
	public:
		TessellationSink^ Open()
		{
			ID2D1TessellationSink *tessellationSink;
			HRESULT hr = GetNative()->Open(&tessellationSink);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return gcnew TessellationSink(tessellationSink);
		}
	internal:
		ID2D1Mesh *GetNative() new 
		{
			return (ID2D1Mesh *)D2DResource::GetNative();
		}
	};
}}}