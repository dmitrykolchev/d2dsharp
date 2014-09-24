/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "WicBitmapCodecInfo.h"
#include "WicBitmapEncoder.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
{
	public ref class WicBitmapEncoderInfo: WicBitmapCodecInfo
	{
	internal:
		WicBitmapEncoderInfo(IWICBitmapEncoderInfo* native): WicBitmapCodecInfo(native)
		{
		}
	public:
		WicBitmapEncoder^ CreateInstance()
		{
			IWICBitmapEncoder* encoder;
			ComUtils::CheckResult(GetNative<IWICBitmapEncoderInfo>()->CreateInstance(&encoder));
			return gcnew WicBitmapEncoder(encoder);
		}
	};
}}}