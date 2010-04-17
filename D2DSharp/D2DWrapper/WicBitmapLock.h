/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
{
	public ref class WicBitmapLock: ComWrapper
	{
	internal:
		WicBitmapLock(IWICBitmapLock* native): ComWrapper(native)
		{
		}
	public:
	internal:
		IWICBitmapLock* GetNative()
		{
			return (IWICBitmapLock*)ComWrapper::GetNative();
		}
	};
}}}