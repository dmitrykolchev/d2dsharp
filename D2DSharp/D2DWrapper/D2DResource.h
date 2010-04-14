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
	ref class Direct2DFactory;

	public ref class D2DResource abstract: ComWrapper
	{
	internal:
		D2DResource(ID2D1Resource* native): 
			ComWrapper(native)
		{
		}

	public:
		Direct2DFactory^ GetFactory();

	internal:
		inline ID2D1Resource* GetNative()
		{
			return (ID2D1Resource*)ComWrapper::GetNative();
		}
	};
}}}