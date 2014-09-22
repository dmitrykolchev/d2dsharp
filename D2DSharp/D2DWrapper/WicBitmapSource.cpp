/*
*
* Authors:
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*
*/
#include "Stdafx.h"

#include "WicBitmapSource.h"


namespace Managed {
	namespace Graphics {
		namespace Imaging
		{
			void WicBitmapSource::CopyPalette(WicPalette^ palette)
			{
				ComUtils::CheckResult(GetNative<IWICBitmapSource>()->CopyPalette(palette->GetNative<IWICPalette>()));
			}

			void WicBitmapSource::CopyPixels(WicRect rect, int stride, array<Byte>^ buffer)
			{
				pin_ptr<Byte> pBuffer = &buffer[0];
				ComUtils::CheckResult(GetNative<IWICBitmapSource>()->CopyPixels((WICRect*) &rect, (UINT) stride, buffer->Length, (BYTE*) pBuffer));
			}
		}
	}
}