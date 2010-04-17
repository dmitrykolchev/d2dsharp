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

namespace Managed { namespace Graphics { namespace DirectWrite
{
	public ref class FontFace: ComWrapper
	{
	internal:
		FontFace(IDWriteFontFace* native): ComWrapper(native)
		{
		}
		FontFace(IDWriteFontFace* native, Boolean addRef): ComWrapper(native, addRef)
		{
		}
	internal:
		IDWriteFontFace* GetNative() new
		{
			return static_cast<IDWriteFontFace*>(ComWrapper::GetNative());
		}
	};
}}}