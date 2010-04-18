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

namespace D2D = Managed::Graphics::Direct2D;

namespace Managed { namespace Graphics { namespace Imaging
{
	ref class WicPalette;
	ref class WicBitmapLock;

	[Flags]
	public enum class WicBitmapLockFlags
	{
		Read = WICBitmapLockRead,
		Write = WICBitmapLockWrite
	};

	public ref class WicBitmap: WicBitmapSource
	{
	internal:
		WicBitmap(IWICBitmap* native): WicBitmapSource(native)
		{
		}
	public:
		WicBitmapLock^ Lock(D2D::RectU lockRect, WicBitmapLockFlags flags);
		void SetPalette(WicPalette^ palette);
		void SetResolution(Double dpiX, Double dpiY);
	internal:
		IWICBitmap* GetNative()
		{
			return (IWICBitmap*)WicBitmapSource::GetNative();
		}
	};
}}}