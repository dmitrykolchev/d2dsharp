/* 
* Bitmap.h 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace Direct2D 
{
	[StructLayout(LayoutKind::Sequential)]
	public value struct BitmapProperties
	{
	private:
		PixelFormat _pixelFormat;
		FLOAT _dpiX;
		FLOAT _dpiY;
	public:
		BitmapProperties(PixelFormat pixelFormat, FLOAT dpiX, FLOAT dpiY)
		{
			_pixelFormat = pixelFormat;
			_dpiX = dpiX;
			_dpiY = dpiY;
		}
	};
	
	ref class RenderTarget;

	public ref class Bitmap: D2DResource
	{
	internal:
		Bitmap(ID2D1Bitmap *native): 
			D2DResource(native)
		{
		}
	public:
		void CopyFromBitmap(PointU destPoint, Bitmap^ bitmap, RectU srcRect);
		void CopyFromRenderTarget(PointU destPoint, RenderTarget^ renderTarget, RectU srcRect);
		void CopyFromMemory(RectU dstRect, IntPtr srcData, UInt32 pitch);
		void CopyFromMemory(RectU dstRect, array<Byte>^ srcData, UInt32 pitch);

		void GetDpi([OutAttribute()]Single% dpiX, [OutAttribute()]Single% dpiY)
		{
			FLOAT x, y;
			GetNative<ID2D1Bitmap>()->GetDpi(&x, &y);
			dpiX = x;
			dpiY = y;
		}
		
		property Managed::Graphics::Direct2D::PixelFormat PixelFormat 
		{ 
			Managed::Graphics::Direct2D::PixelFormat get()
			{
				return Managed::Graphics::Direct2D::PixelFormat(GetNative<ID2D1Bitmap>()->GetPixelFormat());
			} 
		}

		property SizeU PixelSize 
		{ 
			SizeU get()
			{
				return SizeU(GetNative<ID2D1Bitmap>()->GetPixelSize());
			}
		}

		property SizeF Size 
		{
			SizeF get()
			{
				return SizeF(GetNative<ID2D1Bitmap>()->GetSize());
			}
		}
	};
}}}