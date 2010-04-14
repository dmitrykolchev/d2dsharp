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
#include "RenderTarget.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class DCRenderTarget: RenderTarget
	{
	internal:
		DCRenderTarget(ID2D1DCRenderTarget *native): 
			RenderTarget(native)
		{
		}
	public:
		void BindDC(IntPtr hDC, int left, int top, int right, int bottom)
		{
			RECT rect = { left, top, right, bottom };
			HRESULT hr = GetNative()->BindDC((HDC)hDC.ToPointer(), &rect);
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}
	internal:
		ID2D1DCRenderTarget *GetNative() new
		{
			return (ID2D1DCRenderTarget *)RenderTarget::GetNative();
		}
	};
}}}
