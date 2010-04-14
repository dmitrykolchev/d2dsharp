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

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Imaging
{
	ref class WicBitmapSource;

	public ref class WicPalette: ComWrapper
	{
	internal:
		WicPalette(IWICPalette* native): ComWrapper(native)
		{
		}
	public:
		
		array<WicColor>^ GetColors();
		property BitmapPaletteType PaletteType
		{
			BitmapPaletteType get()
			{
				WICBitmapPaletteType value;
				HRESULT hr = GetNative()->GetType(&value);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return (BitmapPaletteType)value;
			}
		}
		property Boolean HasAlpha
		{
			Boolean get()
			{
				BOOL value;
				HRESULT hr = GetNative()->HasAlpha(&value);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return value ? true : false;
			}
		}
		void Initialize(array<WicColor>^ colors);
		void Initialize(WicBitmapSource^ surface, int colorCount, Boolean addTransparentColor);
		void Initialize(WicPalette^ source);
		void Initialize(BitmapPaletteType paletteType, Boolean addTransparentColor)
		{
			HRESULT hr = GetNative()->InitializePredefined((WICBitmapPaletteType)paletteType, (BOOL)addTransparentColor);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}
		property Boolean IsBlackWhite
		{
			Boolean get()
			{
				BOOL value;
				HRESULT hr = GetNative()->IsBlackWhite(&value);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return value ? true : false;
			}
		}
		property Boolean IsGrayscale
		{
			Boolean get()
			{
				BOOL value;
				HRESULT hr = GetNative()->IsGrayscale(&value);
				if(FAILED(hr))
					Marshal::ThrowExceptionForHR(hr);
				return value ? true : false;
			}
		}
	internal:
		IWICPalette* GetNative()
		{
			return (IWICPalette*)ComWrapper::GetNative();
		}
	};
}}}