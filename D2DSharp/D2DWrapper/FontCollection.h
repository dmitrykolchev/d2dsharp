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