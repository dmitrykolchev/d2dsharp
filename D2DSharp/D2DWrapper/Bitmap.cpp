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
		ComUtils::CheckResult(GetNative()->CopyFromBitmap(
			(D2D1_POINT_2U *)&destPoint,
			bitmap->GetNative(),
			(D2D1_RECT_U *)&srcRect));
	}

	void Bitmap::CopyFromRenderTarget(PointU destPoint, RenderTarget^ renderTarget, RectU srcRect)
	{
		ComUtils::CheckResult(GetNative()->CopyFromRenderTarget(
			(D2D1_POINT_2U *)&destPoint,
			renderTarget->GetNative(),
			(D2D1_RECT_U *)&srcRect));
	}

	void Bitmap::CopyFromMemory(RectU dstRect, IntPtr srcData, UInt32 pitch)
	{
		ComUtils::CheckResult(GetNative()->CopyFromMemory(
			(D2D1_RECT_U *)&dstRect,
			srcData.ToPointer(),
			pitch));
	}

	void Bitmap::CopyFromMemory(RectU dstRect, array<Byte>^ srcData, UInt32 pitch)
	{
		pin_ptr<Byte> p = &srcData[0];
		ComUtils::CheckResult(GetNative()->CopyFromMemory(
			(D2D1_RECT_U *)&dstRect,
			p,
			pitch));
	}

}}}
