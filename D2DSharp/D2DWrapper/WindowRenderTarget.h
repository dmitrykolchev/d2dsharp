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
#include "RenderTarget.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	[FlagsAttribute()]
	public enum class WindowState
	{
		None = 0x0000000,
		Occluded = 0x0000001,
	};


	ref class SolidColorBrush;

	public ref class WindowRenderTarget: RenderTarget
	{
	internal:
		WindowRenderTarget(ID2D1HwndRenderTarget* renderTarget): RenderTarget(renderTarget)
		{
		}

	public:
		property WindowState State
		{
			WindowState get()
			{
				int state = GetNative()->CheckWindowState();
				return (WindowState)state;
			}
		}

		property IntPtr Handle
		{
			IntPtr get()
			{
				HWND hwnd = GetNative()->GetHwnd();
				return IntPtr((void*)hwnd);
			}
		}

		void Resize(SizeU size)
		{
			HRESULT hr = GetNative()->Resize(reinterpret_cast<D2D1_SIZE_U*>(&size));
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}

	internal:
		ID2D1HwndRenderTarget *GetNative() new
		{
			return reinterpret_cast<ID2D1HwndRenderTarget *>(RenderTarget::GetNative());
		}

	};
}}}