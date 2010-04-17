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

#include "WicBitmapSource.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Imaging
{
	ref class WicPalette;
	ref class WicBitmapLock;

	[FlagsAttribute()]
	public enum class WicBitmapLockFlags
	{
		Read = WICBitmapLockRead,
		Write = WICBitmapLockWrite
	};

	public ref class WicBitmap: WicBitmapSource
	{
	internal:
		WicBitmap(IWICBitmap* native): WicBitmapSource(native)
		{
		}
	public:
		WicBitmapLock^ Lock(DykBits::Graphics::Direct2D::RectU lockRect, WicBitmapLockFlags flags);
		void SetPalette(WicPalette^ palette);
		void SetResolution(Double dpiX, Double dpiY);
	internal:
		IWICBitmap* GetNative()
		{
			return (IWICBitmap*)WicBitmapSource::GetNative();
		}
	};
}}}