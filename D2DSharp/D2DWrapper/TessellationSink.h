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

#include "ComWrapper.h"
#include "D2DCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DykBits::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class TessellationSink: ComWrapper
	{
	internal:
		TessellationSink(ID2D1TessellationSink *native):
			ComWrapper(native)
		{
		}
	public:
		void AddTriangles(array<Triangle>^ triangles)
		{
			pin_ptr<Triangle> p = &triangles[0];
			GetNative()->AddTriangles((D2D1_TRIANGLE *)p, triangles->Length);
		}

		void Close()
		{
			HRESULT hr = GetNative()->Close();
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}

	internal:
		ID2D1TessellationSink *GetNative() new 
		{
			return (ID2D1TessellationSink *)ComWrapper::GetNative();
		}
	};
}}}