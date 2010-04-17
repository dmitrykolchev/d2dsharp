/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicBitmap.h"


namespace Managed { namespace Graphics { namespace Imaging
{
	void WicBitmap::SetPalette(WicPalette^ palette)
	{
		if(palette == nullptr)
			throw gcnew ArgumentNullException("palette");
		ComUtils::CheckResult(GetNative()->SetPalette(palette->GetNative()));
	}

	void WicBitmap::SetResolution(Double dpiX, Double dpiY)
	{
		ComUtils::CheckResult(GetNative()->SetResolution(dpiX, dpiY));
	}

	WicBitmapLock^ WicBitmap::Lock(Managed::Graphics::Direct2D::RectU lockRect, WicBitmapLockFlags flags)
	{
		WICRect rect = { lockRect.X, lockRect.Y, lockRect.Width, lockRect.Height };
		IWICBitmapLock* pLock;
		ComUtils::CheckResult(GetNative()->Lock(&rect, (DWORD)flags, &pLock));
		return gcnew WicBitmapLock(pLock);
	}
}}}