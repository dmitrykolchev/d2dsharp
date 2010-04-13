#include "Stdafx.h"

#include "WicFormatConverter.h"

namespace DykBits { namespace Graphics { namespace Imaging
{
	void WicFormatConverter::Convert(WicBitmapSource^ source, Guid dstPixelFormat, BitmapDitherType dither, WicPalette^ palette, Double alphaThresholdPercent, BitmapPaletteType paletteType)
	{
		IWICPalette *p = palette == nullptr ? NULL : palette->GetNative();

		HRESULT hr = GetNative()->Initialize(
			source->GetNative(), 
			*(GUID*)&dstPixelFormat,
			(WICBitmapDitherType)dither,
			p,
			alphaThresholdPercent,
			(WICBitmapPaletteType)paletteType);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}
}}}