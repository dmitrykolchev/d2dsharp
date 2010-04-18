#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class FontFileLoader: ComWrapper
	{
	internal:
		FontFileLoader(IDWriteFontFileLoader* native): ComWrapper(native)
		{
		}

	internal:
		IDWriteFontFileLoader* GetNative() new 
		{
			return (IDWriteFontFileLoader*)ComWrapper::GetNative();
		}
	};
}}}