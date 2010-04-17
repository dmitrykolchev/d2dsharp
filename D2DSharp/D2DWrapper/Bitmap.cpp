/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/

#include "stdafx.h"

#include "Bitmap.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	void Bitmap::CopyFromBitmap(PointU destPoint, Bitmap^ bitmap, RectU srcRect)
	{
		HRESULT hr = GetNative()->CopyFromBitmap(
			(D2D1_POINT_2U *)&destPoint,
			bitmap->GetNative(),
			(D2D1_RECT_U *)&srcRect);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void Bitmap::CopyFromRenderTarget(PointU destPoint, RenderTarget^ renderTarget, RectU srcRect)
	{
		HRESULT hr = GetNative()->CopyFromRenderTarget(
			(D2D1_POINT_2U *)&destPoint,
			renderTarget->GetNative(),
			(D2D1_RECT_U *)&srcRect);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void Bitmap::CopyFromMemory(RectU dstRect, IntPtr srcData, UInt32 pitch)
	{
		HRESULT hr = GetNative()->CopyFromMemory(
			(D2D1_RECT_U *)&dstRect,
			srcData.ToPointer(),
			pitch);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void Bitmap::CopyFromMemory(RectU dstRect, array<Byte>^ srcData, UInt32 pitch)
	{
		pin_ptr<Byte> p = &srcData[0];
		HRESULT hr = GetNative()->CopyFromMemory(
			(D2D1_RECT_U *)&dstRect,
			p,
			pitch);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

}}}
