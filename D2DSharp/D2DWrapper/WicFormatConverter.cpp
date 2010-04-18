/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicFormatConverter.h"

namespace Managed { namespace Graphics { namespace Imaging
{
	void WicFormatConverter::Convert(WicBitmapSource^ source, Guid dstPixelFormat, BitmapDitherType dither, WicPalette^ palette, Double alphaThresholdPercent, BitmapPaletteType paletteType)
	{
		IWICPalette *p = palette == nullptr ? NULL : palette->GetNative();

		ComUtils::CheckResult(GetNative()->Initialize(
			source->GetNative(), 
			*(GUID*)&dstPixelFormat,
			(WICBitmapDitherType)dither,
			p,
			alphaThresholdPercent,
			(WICBitmapPaletteType)paletteType));
	}
}}}