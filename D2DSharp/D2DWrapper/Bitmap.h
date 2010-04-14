/* 
* Bitmap.h 
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

using namespace System;
using namespace System::Runtime::InteropServices;


namespace DykBits { namespace Graphics { namespace Direct2D 
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
			GetNative()->GetDpi(&x, &y);
			dpiX = x;
			dpiY = y;
		}
		
		property DykBits::Graphics::Direct2D::PixelFormat PixelFormat 
		{ 
			DykBits::Graphics::Direct2D::PixelFormat get()
			{
				return DykBits::Graphics::Direct2D::PixelFormat(GetNative()->GetPixelFormat());
			} 
		}

		property SizeU PixelSize 
		{ 
			SizeU get()
			{
				return SizeU(GetNative()->GetPixelSize());
			}
		}

		property SizeF Size 
		{
			SizeF get()
			{
				return SizeF(GetNative()->GetSize());
			}
		}
	internal:
		ID2D1Bitmap *GetNative() new
		{
			return (ID2D1Bitmap *)D2DResource::GetNative();
		}
	};
}}}