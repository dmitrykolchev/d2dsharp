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

#include "WicBitmap.h"


namespace DykBits { namespace Graphics { namespace Imaging
{
	void WicBitmap::SetPalette(WicPalette^ palette)
	{
		if(palette == nullptr)
			throw gcnew ArgumentNullException("palette");
		ComUtils::CheckResult(GetNative()->SetPalette(palette->GetNative()));
	}

	void WicBitmap::SetResolution(Double dpiX, Double dpiY)
	{
		ComUtils::CheckResult(GetNative()->SetResolution(dpiX, dpiY));
	}

	WicBitmapLock^ WicBitmap::Lock(DykBits::Graphics::Direct2D::RectU lockRect, WicBitmapLockFlags flags)
	{
		WICRect rect = { lockRect.X, lockRect.Y, lockRect.Width, lockRect.Height };
		IWICBitmapLock* pLock;
		ComUtils::CheckResult(GetNative()->Lock(&rect, (DWORD)flags, &pLock));
		return gcnew WicBitmapLock(pLock);
	}
}}}