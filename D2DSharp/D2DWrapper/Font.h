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
	ref class FontFace;
	ref class LocalizedStrings;
	ref class FontFamily;

	public ref class Font: ComWrapper
	{
	internal:
		Font(IDWriteFont* native): ComWrapper(native)
		{
		}
	public:
		FontFace^ CreateFontFace();
		property LocalizedStrings^ FaceNames { LocalizedStrings^ get(); }
		property FontFamily^ Family { FontFamily^ get(); }
		LocalizedStrings^ GetInformationalStrings(InformationalStringId id, [Out]Boolean% exists);
		LocalizedStrings^ GetInformationalStrings(InformationalStringId id);
		property FontMetrics Metrics { FontMetrics get(); }
		property FontSimulations Simulations { FontSimulations get(); }
		property FontStretch Stretch { FontStretch get(); }
		property FontStyle Style { FontStyle get(); }
		property FontWeight Weight { FontWeight get(); }
		Boolean HasCharacter(UInt32 unicodeValue);
		property Boolean IsSymbolFont { Boolean get(); }
	internal:
		IDWriteFont* GetNative() new
		{
			return static_cast<IDWriteFont*>(ComWrapper::GetNative());
		}
	};
}}}
