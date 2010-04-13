#pragma once

#include "WicCommon.h"
#include "WicBitmapSource.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Imaging
{
	ref class WicBitmapSource;
	ref class WicPalette;

	public ref class WicFormatConverter: WicBitmapSource
	{
	internal:
		WicFormatConverter(IWICFormatConverter* native): WicBitmapSource(native)
		{
		}
	public:
		Boolean CanConvert(Guid srcPixelFormat, Guid dstPixelFormat)
		{
			BOOL value;
			HRESULT hr = GetNative()->CanConvert(*(GUID*)&srcPixelFormat, *(GUID*)&dstPixelFormat, &value);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return value ? true : false;
		}
		void Convert(WicBitmapSource^ source, Guid dstPixelFormat, BitmapDitherType dither, WicPalette^ palette, Double alphaThresholdPercent, BitmapPaletteType paletteType);
	internal:
		IWICFormatConverter* GetNative() new 
		{
			return (IWICFormatConverter*)WicBitmapSource::GetNative();
		}
	};
}}}