#pragma once

#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DykBits::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace DirectWrite 
{
	public ref class FontCollection: ComWrapper
	{
	internal:
		FontCollection(IDWriteFontCollection* native): 
			ComWrapper(native)
		{
		}
	internal:
		IDWriteFontCollection* GetNative() new
		{
			return (IDWriteFontCollection*)ComWrapper::GetNative();
		}
	public:

	};
}}}