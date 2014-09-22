/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "WicCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
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
			ComUtils::CheckResult(GetNative<IWICFormatConverter>()->CanConvert(*(GUID*) &srcPixelFormat, *(GUID*) &dstPixelFormat, &value));
			return value != 0;
		}
		void Convert(WicBitmapSource^ source, Guid dstPixelFormat, BitmapDitherType dither, WicPalette^ palette, Double alphaThresholdPercent, BitmapPaletteType paletteType);
	};
}}}