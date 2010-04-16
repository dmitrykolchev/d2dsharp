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

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Imaging
{
	public ref class WicStream: ComWrapper
	{
	internal:
		WicStream(IWICStream* native): ComWrapper(native)
		{
		}
	public:
		void Initialize(Type^ type, String^ resourceName);
		void Initialize(String^ fileName, DesiredAccess desiredAccess);
		void Initialize(Stream^ stream);
		void Initialize(Stream^ stream, UInt64 offset, UInt64 maxSize);
		void Initialize(array<Byte>^ buffer);
	internal:
		IWICStream* GetNative()
		{
			return (IWICStream*)ComWrapper::GetNative();
		}
	};
}}}