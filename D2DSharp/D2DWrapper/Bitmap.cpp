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

#include "stdafx.h"

#include "Bitmap.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	void Bitmap::CopyFromBitmap(PointU destPoint, Bitmap^ bitmap, RectU srcRect)
	{
		HRESULT hr = GetNative()->CopyFromBitmap(
			(D2D1_POINT_2U *)&destPoint,
			bitmap->GetNative(),
			(D2D1_RECT_U *)&srcRect);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void Bitmap::CopyFromRenderTarget(PointU destPoint, RenderTarget^ renderTarget, RectU srcRect)
	{
		HRESULT hr = GetNative()->CopyFromRenderTarget(
			(D2D1_POINT_2U *)&destPoint,
			renderTarget->GetNative(),
			(D2D1_RECT_U *)&srcRect);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void Bitmap::CopyFromMemory(RectU dstRect, IntPtr srcData, UInt32 pitch)
	{
		HRESULT hr = GetNative()->CopyFromMemory(
			(D2D1_RECT_U *)&dstRect,
			srcData.ToPointer(),
			pitch);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

	void Bitmap::CopyFromMemory(RectU dstRect, array<Byte>^ srcData, UInt32 pitch)
	{
		pin_ptr<Byte> p = &srcData[0];
		HRESULT hr = GetNative()->CopyFromMemory(
			(D2D1_RECT_U *)&dstRect,
			p,
			pitch);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
	}

}}}
