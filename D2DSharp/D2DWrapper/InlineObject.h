/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "ComWrapper.h"
#include "ComUtils.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class InlineObject: ComWrapper
	{
	internal:
		InlineObject(IDWriteInlineObject* native): ComWrapper(native) 
		{
		}
		InlineObject(IDWriteInlineObject* native, Boolean addRef): ComWrapper(native, addRef) 
		{
		}
	internal:
		IDWriteInlineObject* GetNative() new
		{
			return static_cast<IDWriteInlineObject*>(ComWrapper::GetNative());
		}
	};
}}}