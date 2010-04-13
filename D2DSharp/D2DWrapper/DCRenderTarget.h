#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"
#include "RenderTarget.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class DCRenderTarget: RenderTarget
	{
	internal:
		DCRenderTarget(ID2D1DCRenderTarget *native): 
			RenderTarget(native)
		{
		}
	public:
		void BindDC(IntPtr hDC, int left, int top, int right, int bottom)
		{
			RECT rect = { left, top, right, bottom };
			HRESULT hr = GetNative()->BindDC((HDC)hDC.ToPointer(), &rect);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}
	internal:
		ID2D1DCRenderTarget *GetNative() new
		{
			return (ID2D1DCRenderTarget *)RenderTarget::GetNative();
		}
	};
}}}
