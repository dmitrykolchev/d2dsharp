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
	ref class Font;
	ref class FontCollection;

	public ref class FontList: ComWrapper
	{
	internal:
		FontList(IDWriteFontList* native): ComWrapper(native)
		{
		}
	public:
		property Int32 Count { Int32 get(); }
		property Font^ default[Int32] { Font^ get(Int32 index); }
		property FontCollection^ Parent { FontCollection^ get(); }
	};
}}}
