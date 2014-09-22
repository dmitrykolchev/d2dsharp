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
		IWICPalette *p = palette == nullptr ? NULL : palette->GetNative<IWICPalette>();

		ComUtils::CheckResult(GetNative<IWICFormatConverter>()->Initialize(
			source->GetNative<IWICBitmapSource>(), 
			*(GUID*)&dstPixelFormat,
			(WICBitmapDitherType)dither,
			p,
			alphaThresholdPercent,
			(WICBitmapPaletteType)paletteType));
	}
}}}