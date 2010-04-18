/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"
#include "RenderTarget.h"
#include "Bitmap.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	public ref class BitmapRenderTarget: RenderTarget
	{
	internal:
		BitmapRenderTarget(ID2D1BitmapRenderTarget *native): 
			RenderTarget(native)
		{
		}
	public:
		property Managed::Graphics::Direct2D::Bitmap^ Bitmap
		{
			Managed::Graphics::Direct2D::Bitmap^ get()
			{
				ID2D1Bitmap *bitmap;
				ComUtils::CheckResult(GetNative()->GetBitmap(&bitmap));
				return gcnew Managed::Graphics::Direct2D::Bitmap(bitmap);
			}
		}
	internal:
		ID2D1BitmapRenderTarget *GetNative() new
		{
			return (ID2D1BitmapRenderTarget *)RenderTarget::GetNative();
		}
	};
}}}
