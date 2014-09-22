/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "WicBitmapSource.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
{
	public ref class WicBitmapFrameDecode: WicBitmapSource
	{
	internal:
		WicBitmapFrameDecode(IWICBitmapFrameDecode* native): WicBitmapSource(native)
		{
		}
	public:
	};
}}}