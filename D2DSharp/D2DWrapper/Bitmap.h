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
	public ref class BitmapProperties
	{
	private:
		PixelFormat _pixelFormat;
		FLOAT _dpiX;
		FLOAT _dpiY;
	public:
		BitmapProperties()
		{
			_pixelFormat = PixelFormat::Default;
			_dpiX = 96.0f;
			_dpiY = 96.0f;
		}
		BitmapProperties(PixelFormat pixelFormat, FLOAT dpiX, FLOAT dpiY)
		{
			_pixelFormat = pixelFormat;
			_dpiX = dpiX;
			_dpiY = dpiY;
		}
		property PixelFormat Format
		{
			PixelFormat get() { return this->_pixelFormat; }
			void set(PixelFormat value) { this->_pixelFormat = value; }
		}
		property FLOAT DpiX
		{
			FLOAT get() { return this->_dpiX; }
			void set(FLOAT value) { this->_dpiX = value; }
		}
		property FLOAT DpiY
		{
			FLOAT get() { return this->_dpiY; }
			void set(FLOAT value) { this->_dpiY = value; }
		}
	};

	[FlagsAttribute]
	public enum class BitmapOptions
	{
		None = 0,
		Target = 1,
		CannotDraw = 2,
		CpuRead = 4,
		GdiCompatible = 8
	};

	ref class RenderTarget;

	public ref class Image abstract: D2DResource
	{
	protected:
		Image(ID2D1Image* native):
			D2DResource(native)
		{
		}
	};

	public ref class Bitmap: Image
	{
	internal:
		Bitmap(ID2D1Bitmap *native): 
			Image(native)
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

	public ref class Bitmap1: Bitmap
	{
	internal:
		Bitmap1(ID2D1Bitmap1* native): 
			Bitmap(native)
		{
		}
	};
}}}