#include "Stdafx.h"

#include "WicBitmapSource.h"


namespace DykBits { namespace Graphics { namespace Imaging
{
	void WicBitmapSource::CopyPalette(WicPalette^ palette)
	{
		HRESULT hr = GetNative()->CopyPalette(palette->GetNative());
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void WicBitmapSource::CopyPixels(WicRect rect, int stride, array<Byte>^ buffer)
	{
		pin_ptr<Byte> pBuffer = &buffer[0];
		HRESULT hr = GetNative()->CopyPixels((WICRect*)&rect, (UINT)stride, buffer->Length, (BYTE*)pBuffer);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}
}}}