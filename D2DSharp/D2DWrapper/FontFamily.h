/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;
using namespace Managed::Graphics::Direct2D;

namespace Managed { namespace Graphics { namespace DirectWrite
{
	ref class LocalizedStrings;
	ref class Font;
	ref class FontList;

	public ref class FontFamily: ComWrapper
	{
	internal:
		FontFamily(IDWriteFontFamily* native): ComWrapper(native)
		{
		}
	public:
		property LocalizedStrings^ FamilyNames { LocalizedStrings^ get(); }
		Font^ GetFirstMatchingFont(FontWeight weight, FontStretch stretch, FontStyle style);
		FontList^ GetMatchingFonts(FontWeight weight, FontStretch stretch, FontStyle style);
	};
}}}
