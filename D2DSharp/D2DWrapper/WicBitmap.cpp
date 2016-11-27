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
		ComUtils::CheckResult(GetNative<IWICBitmap>()->SetPalette(palette->GetNative<IWICPalette>()));
	}

	void WicBitmap::SetResolution(Double dpiX, Double dpiY)
	{
		ComUtils::CheckResult(GetNative<IWICBitmap>()->SetResolution(dpiX, dpiY));
	}

	WicBitmapLock^ WicBitmap::Lock(Managed::Graphics::Direct2D::RectU lockRect, WicBitmapLockFlags flags)
	{
		WICRect rect = { (INT)lockRect.X, (INT)lockRect.Y, (INT)lockRect.Width, (INT)lockRect.Height };
		IWICBitmapLock* pLock;
		ComUtils::CheckResult(GetNative<IWICBitmap>()->Lock(&rect, (DWORD) flags, &pLock));
		return gcnew WicBitmapLock(pLock);
	}
}}}