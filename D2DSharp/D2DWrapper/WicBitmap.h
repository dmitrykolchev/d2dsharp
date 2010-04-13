#pragma once

#include "WicBitmapSource.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Imaging
{
	public ref class WicBitmap: WicBitmapSource
	{
	internal:
		WicBitmap(IWICBitmap* native): WicBitmapSource(native)
		{
		}
	public:

	internal:
		IWICBitmap* GetNative()
		{
			return (IWICBitmap*)WicBitmapSource::GetNative();
		}
	};
}}}