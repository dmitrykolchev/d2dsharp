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

#include "WicCommon.h"
#include "WicBitmapSource.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Imaging
{
	ref class WicBitmapSource;
	ref class WicPalette;

	public ref class WicFormatConverter: WicBitmapSource
	{
	internal:
		WicFormatConverter(IWICFormatConverter* native): WicBitmapSource(native)
		{
		}
	public:
		Boolean CanConvert(Guid srcPixelFormat, Guid dstPixelFormat)
		{
			BOOL value;
			HRESULT hr = GetNative()->CanConvert(*(GUID*)&srcPixelFormat, *(GUID*)&dstPixelFormat, &value);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
			return value ? true : false;
		}
		void Convert(WicBitmapSource^ source, Guid dstPixelFormat, BitmapDitherType dither, WicPalette^ palette, Double alphaThresholdPercent, BitmapPaletteType paletteType);
	internal:
		IWICFormatConverter* GetNative() new 
		{
			return (IWICFormatConverter*)WicBitmapSource::GetNative();
		}
	};
}}}