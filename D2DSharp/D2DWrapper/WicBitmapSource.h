/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#include "WicCommon.h"

namespace Managed { namespace Graphics { namespace Imaging
{
	ref class WicPalette;

	public ref class WicBitmapSource: ComWrapper
	{
	internal:
		WicBitmapSource(IWICBitmapSource* native): ComWrapper(native)
		{
		}
	public:
		void CopyPalette(WicPalette^ palette);
		void CopyPixels(WicRect rect, int stride, array<Byte>^ buffer);
		property Guid PixelFormat
		{
			Guid get()
			{
				Guid guid;
				ComUtils::CheckResult(GetNative()->GetPixelFormat((WICPixelFormatGUID*)&guid));
				return guid;
			}
		}
		void GetResolution([OutAttribute()]Double% dpiX, [OutAttribute()]Double% dpiY)
		{
			double x, y;
			ComUtils::CheckResult(GetNative()->GetResolution((double*)&x, (double*)&y));
			dpiX = x;
			dpiY = y;
		}
		property Managed::Graphics::Direct2D::SizeU Size
		{
			Managed::Graphics::Direct2D::SizeU get()
			{
				UINT32 width, height;
				ComUtils::CheckResult(GetNative()->GetSize(&width, &height));
				return Managed::Graphics::Direct2D::SizeU(width, height);
			}
		}

	internal:
		IWICBitmapSource* GetNative()
		{
			return (IWICBitmapSource*)ComWrapper::GetNative();
		}
	};
}}}