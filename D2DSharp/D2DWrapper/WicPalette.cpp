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
		IWICPalette* palette = GetNative();
		UINT count;
		HRESULT hr = palette->GetColorCount(&count);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		array<WicColor>^ colors = gcnew array<WicColor>(count);
		pin_ptr<WicColor> pColors = &colors[0];
		UINT actualColors;
		hr = palette->GetColors(count, (WICColor*)pColors, &actualColors);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return colors;
	}

	void WicPalette::Initialize(array<WicColor>^ colors)
	{
		if(colors == nullptr)
			throw gcnew ArgumentNullException("colors");

		pin_ptr<WicColor> pColors = &colors[0];
		HRESULT hr = GetNative()->InitializeCustom((WICColor*)pColors, colors->Length);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void WicPalette::Initialize(WicBitmapSource^ surface, int colorCount, Boolean addTransparentColor)
	{
		HRESULT hr = GetNative()->InitializeFromBitmap(surface->GetNative(), (UINT)colorCount, (BOOL)addTransparentColor);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void WicPalette::Initialize(WicPalette^ source)
	{
		HRESULT hr = GetNative()->InitializeFromPalette(source->GetNative());
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

}}}