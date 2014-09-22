/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicPalette.h"


namespace Managed { namespace Graphics { namespace Imaging
{
	array<WicColor>^ WicPalette::GetColors()
	{
		IWICPalette* palette = GetNative<IWICPalette>();
		UINT count;
		ComUtils::CheckResult(palette->GetColorCount(&count));

		array<WicColor>^ colors = gcnew array<WicColor>(count);
		pin_ptr<WicColor> pColors = &colors[0];
		UINT actualColors;
		ComUtils::CheckResult(palette->GetColors(count, (WICColor*)pColors, &actualColors));
		return colors;
	}

	void WicPalette::Initialize(array<WicColor>^ colors)
	{
		if(colors == nullptr)
			throw gcnew ArgumentNullException("colors");

		pin_ptr<WicColor> pColors = &colors[0];
		ComUtils::CheckResult(GetNative<IWICPalette>()->InitializeCustom((WICColor*) pColors, colors->Length));
	}

	void WicPalette::Initialize(WicBitmapSource^ surface, int colorCount, Boolean addTransparentColor)
	{
		ComUtils::CheckResult(GetNative<IWICPalette>()->InitializeFromBitmap(surface->GetNative<IWICBitmapSource>(), (UINT) colorCount, (BOOL) addTransparentColor));
	}

	void WicPalette::Initialize(WicPalette^ source)
	{
		ComUtils::CheckResult(GetNative<IWICPalette>()->InitializeFromPalette(source->GetNative<IWICPalette>()));
	}

}}}