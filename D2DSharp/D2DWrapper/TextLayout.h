#pragma once

#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DykBits::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace DirectWrite 
{
	public ref class TextLayout: ComWrapper
	{
	internal:
		TextLayout(IDWriteTextLayout* native): 
			ComWrapper(native)
		{
		}
	public:
	internal:
		IDWriteTextLayout* GetNative() new
		{
			return (IDWriteTextLayout*)ComWrapper::GetNative();
		}
	};
}}}