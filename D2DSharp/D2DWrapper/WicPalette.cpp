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
#include "Stdafx.h"

#include "WicPalette.h"


namespace DykBits { namespace Graphics { namespace Imaging
{
	array<WicColor>^ WicPalette::GetColors()
	{
		IWICPalette* palette = GetNative();
		UINT count;
		HRESULT hr = palette->GetColorCount(&count);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		array<WicColor>^ colors = gcnew array<WicColor>(count);
		pin_ptr<WicColor> pColors = &colors[0];
		UINT actualColors;
		hr = palette->GetColors(count, (WICColor*)pColors, &actualColors);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return colors;
	}

	void WicPalette::Initialize(array<WicColor>^ colors)
	{
		if(colors == nullptr)
			throw gcnew ArgumentNullException("colors");

		pin_ptr<WicColor> pColors = &colors[0];
		HRESULT hr = GetNative()->InitializeCustom((WICColor*)pColors, colors->Length);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void WicPalette::Initialize(WicBitmapSource^ surface, int colorCount, Boolean addTransparentColor)
	{
		HRESULT hr = GetNative()->InitializeFromBitmap(surface->GetNative(), (UINT)colorCount, (BOOL)addTransparentColor);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void WicPalette::Initialize(WicPalette^ source)
	{
		HRESULT hr = GetNative()->InitializeFromPalette(source->GetNative());
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

}}}