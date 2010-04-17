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
	public ref class Typography: ComWrapper
	{
	internal:
		Typography(IDWriteTypography* native): ComWrapper(native)
		{
		}
	public:
	internal:
		IDWriteTypography* GetNative() new
		{
			return (IDWriteTypography*)ComWrapper::GetNative();
		}
	};
}}}