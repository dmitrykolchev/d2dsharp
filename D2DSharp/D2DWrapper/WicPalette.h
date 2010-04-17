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

	public ref class WicPalette: ComWrapper
	{
	internal:
		WicPalette(IWICPalette* native): ComWrapper(native)
		{
		}
	public:
		
		array<WicColor>^ GetColors();
		property BitmapPaletteType PaletteType
		{
			BitmapPaletteType get()
			{
				WICBitmapPaletteType value;
				HRESULT hr = GetNative()->GetType(&value);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return (BitmapPaletteType)value;
			}
		}
		property Boolean HasAlpha
		{
			Boolean get()
			{
				BOOL value;
				HRESULT hr = GetNative()->HasAlpha(&value);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return value ? true : false;
			}
		}
		void Initialize(array<WicColor>^ colors);
		void Initialize(WicBitmapSource^ surface, int colorCount, Boolean addTransparentColor);
		void Initialize(WicPalette^ source);
		void Initialize(BitmapPaletteType paletteType, Boolean addTransparentColor)
		{
			HRESULT hr = GetNative()->InitializePredefined((WICBitmapPaletteType)paletteType, (BOOL)addTransparentColor);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}
		property Boolean IsBlackWhite
		{
			Boolean get()
			{
				BOOL value;
				HRESULT hr = GetNative()->IsBlackWhite(&value);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return value ? true : false;
			}
		}
		property Boolean IsGrayscale
		{
			Boolean get()
			{
				BOOL value;
				HRESULT hr = GetNative()->IsGrayscale(&value);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return value ? true : false;
			}
		}
	internal:
		IWICPalette* GetNative()
		{
			return (IWICPalette*)ComWrapper::GetNative();
		}
	};
}}}