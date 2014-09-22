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
				ComUtils::CheckResult(GetNative<IWICPalette>()->GetType(&value));
				return (BitmapPaletteType)value;
			}
		}
		property Boolean HasAlpha
		{
			Boolean get()
			{
				BOOL value;
				ComUtils::CheckResult(GetNative<IWICPalette>()->HasAlpha(&value));
				return value != 0;
			}
		}
		void Initialize(array<WicColor>^ colors);
		void Initialize(WicBitmapSource^ surface, int colorCount, Boolean addTransparentColor);
		void Initialize(WicPalette^ source);
		void Initialize(BitmapPaletteType paletteType, Boolean addTransparentColor)
		{
			ComUtils::CheckResult(GetNative<IWICPalette>()->InitializePredefined((WICBitmapPaletteType) paletteType, (BOOL) addTransparentColor));
		}
		property Boolean IsBlackWhite
		{
			Boolean get()
			{
				BOOL value;
				ComUtils::CheckResult(GetNative<IWICPalette>()->IsBlackWhite(&value));
				return value != 0;
			}
		}
		property Boolean IsGrayscale
		{
			Boolean get()
			{
				BOOL value;
				ComUtils::CheckResult(GetNative<IWICPalette>()->IsGrayscale(&value));
				return value != 0;
			}
		}
	};
}}}