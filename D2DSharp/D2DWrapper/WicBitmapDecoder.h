#pragma once

#include "WicBitmapFrameDecode.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Imaging
{
	public ref class WicBitmapDecoder: ComWrapper
	{
	internal:
		WicBitmapDecoder(IWICBitmapDecoder* native): ComWrapper(native)
		{
		}
	public:
		property int FrameCount
		{
			int get()
			{
				UINT count;
				HRESULT hr = GetNative()->GetFrameCount(&count);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return (int)count;
			}
		}

		WicBitmapFrameDecode^ GetFrame(int index)
		{
			IWICBitmapFrameDecode* frame;
			HRESULT hr = GetNative()->GetFrame((UINT)index, &frame);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return gcnew WicBitmapFrameDecode(frame);
		}
	internal:
		IWICBitmapDecoder* GetNative()
		{
			return (IWICBitmapDecoder*)ComWrapper::GetNative();
		}
	};
}}}