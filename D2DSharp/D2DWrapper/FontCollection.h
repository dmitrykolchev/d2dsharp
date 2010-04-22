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

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	ref class FontFamily;
	ref class FontFace;
	ref class Font;

	public ref class FontCollection: ComWrapper
	{
	internal:
		FontCollection(IDWriteFontCollection* native): 
			ComWrapper(native)
		{
		}
	public:
		property FontFamily^ default[int]
		{
			FontFamily^ get(int index);
		}
		property Int32 Count { Int32 get(); }
		Int32 FindFamilyName(String^ familyName);
		Font^ GetFontFromFontFace(FontFace^ fontFace);
	internal:
		IDWriteFontCollection* GetNative() new
		{
			return (IDWriteFontCollection*)ComWrapper::GetNative();
		}

	};
}}}