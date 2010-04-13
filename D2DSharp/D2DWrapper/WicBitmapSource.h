#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#include "WicCommon.h"

namespace DykBits { namespace Graphics { namespace Imaging
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
	internal:
		IWICBitmapSource* GetNative()
		{
			return (IWICBitmapSource*)ComWrapper::GetNative();
		}
	};
}}}