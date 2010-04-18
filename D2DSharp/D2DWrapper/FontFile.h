#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class FontFile: ComWrapper
	{
	internal:
		FontFile(IDWriteFontFile* native): ComWrapper(native)
		{
		}

	internal:
		IDWriteFontFile* GetNative() new 
		{
			return (IDWriteFontFile*)ComWrapper::GetNative();
		}
	};
}}}