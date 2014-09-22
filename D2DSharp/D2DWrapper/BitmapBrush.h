/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"
#include "Brush.h"
#include "Bitmap.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace Direct2D 
{
	public ref class BitmapBrush: Brush
	{
	internal:
		BitmapBrush(ID2D1BitmapBrush* native):
			Brush(native)
		{
		}
	public:
		property Managed::Graphics::Direct2D::Bitmap^ Bitmap
		{
			Managed::Graphics::Direct2D::Bitmap^ get()
			{
				ID2D1Bitmap *bitmap;
				GetNative<ID2D1BitmapBrush>()->GetBitmap(&bitmap);
				return gcnew Managed::Graphics::Direct2D::Bitmap(bitmap);
			}
			void set(Managed::Graphics::Direct2D::Bitmap^ value)
			{
				GetNative<ID2D1BitmapBrush>()->SetBitmap(value->GetNative<ID2D1Bitmap>());
			}
		}

		property ExtendMode ExtendModeX
		{
			ExtendMode get()
			{
				return (ExtendMode) GetNative<ID2D1BitmapBrush>()->GetExtendModeX();
			}
			void set(ExtendMode value)
			{
				GetNative<ID2D1BitmapBrush>()->SetExtendModeX((D2D1_EXTEND_MODE) value);
			}
		}

		property ExtendMode ExtendModeY
		{
			ExtendMode get()
			{
				return (ExtendMode) GetNative<ID2D1BitmapBrush>()->GetExtendModeY();
			}
			void set(ExtendMode value)
			{
				GetNative<ID2D1BitmapBrush>()->SetExtendModeY((D2D1_EXTEND_MODE) value);
			}
		}

		property BitmapInterpolationMode InterpolationMode
		{
			BitmapInterpolationMode get()
			{
				return (BitmapInterpolationMode) GetNative<ID2D1BitmapBrush>()->GetInterpolationMode();
			}
			void set(BitmapInterpolationMode value)
			{
				GetNative<ID2D1BitmapBrush>()->SetInterpolationMode((D2D1_BITMAP_INTERPOLATION_MODE) value);
			}
		}
	};
}}}