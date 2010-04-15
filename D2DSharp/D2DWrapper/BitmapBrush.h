/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
* Copyright (C) 2010 Dmitry Kolchev
*
* This sourcecode is licenced under The GNU Lesser General Public License
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
* USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"
#include "Brush.h"
#include "Bitmap.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class BitmapBrush: Brush
	{
	internal:
		BitmapBrush(ID2D1BitmapBrush* native):
			Brush(native)
		{
		}
	public:
		property DykBits::Graphics::Direct2D::Bitmap^ Bitmap
		{
			DykBits::Graphics::Direct2D::Bitmap^ get()
			{
				ID2D1Bitmap *bitmap;
				GetNative()->GetBitmap(&bitmap);
				return gcnew DykBits::Graphics::Direct2D::Bitmap(bitmap);
			}
			void set(DykBits::Graphics::Direct2D::Bitmap^ value)
			{
				GetNative()->SetBitmap(value->GetNative());
			}
		}

		property ExtendMode ExtendModeX
		{
			ExtendMode get()
			{
				return (ExtendMode)GetNative()->GetExtendModeX();
			}
			void set(ExtendMode value)
			{
				GetNative()->SetExtendModeX((D2D1_EXTEND_MODE)value);
			}
		}

		property ExtendMode ExtendModeY
		{
			ExtendMode get()
			{
				return (ExtendMode)GetNative()->GetExtendModeY();
			}
			void set(ExtendMode value)
			{
				GetNative()->SetExtendModeY((D2D1_EXTEND_MODE)value);
			}
		}

		property BitmapInterpolationMode InterpolationMode
		{
			BitmapInterpolationMode get()
			{
				return (BitmapInterpolationMode)GetNative()->GetInterpolationMode();
			}
			void set(BitmapInterpolationMode value)
			{
				GetNative()->SetInterpolationMode((D2D1_BITMAP_INTERPOLATION_MODE)value);
			}
		}



	internal:
		ID2D1BitmapBrush* GetNative()
		{
			return (ID2D1BitmapBrush*)Brush::GetNative();
		}
	};
}}}