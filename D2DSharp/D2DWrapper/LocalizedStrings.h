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
	public ref class LocalizedStrings: ComWrapper
	{
	internal:
		LocalizedStrings(IDWriteLocalizedStrings* native): ComWrapper(native)
		{
		}
	public:
		System::Globalization::CultureInfo^ GetCulture(Int32 index);
		Int32 FindCulture(System::Globalization::CultureInfo^ culture);
		property Int32 Count { Int32 get(); }
		property String^ default[Int32] { String^ get(Int32 index); }
	};
}}}
