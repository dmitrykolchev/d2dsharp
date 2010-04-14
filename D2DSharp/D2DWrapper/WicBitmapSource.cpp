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

#include "WicBitmapSource.h"


namespace DykBits { namespace Graphics { namespace Imaging
{
	void WicBitmapSource::CopyPalette(WicPalette^ palette)
	{
		HRESULT hr = GetNative()->CopyPalette(palette->GetNative());
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void WicBitmapSource::CopyPixels(WicRect rect, int stride, array<Byte>^ buffer)
	{
		pin_ptr<Byte> pBuffer = &buffer[0];
		HRESULT hr = GetNative()->CopyPixels((WICRect*)&rect, (UINT)stride, buffer->Length, (BYTE*)pBuffer);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}
}}}