#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class TextAnalyzer: ComWrapper
	{
	internal:
		TextAnalyzer(IDWriteTextAnalyzer* native): ComWrapper(native)
		{
		}

	internal:
		IDWriteTextAnalyzer* GetNative() new 
		{
			return (IDWriteTextAnalyzer*)ComWrapper::GetNative();
		}
	};
}}}