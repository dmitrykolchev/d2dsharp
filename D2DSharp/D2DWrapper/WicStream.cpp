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

#include "WicStream.h"


namespace DykBits { namespace Graphics { namespace Imaging
{
	void WicStream::Initialize(Type^ type, String^ resourceName)
	{
		System::IO::Stream^ stream = type->Assembly->GetManifestResourceStream(type, resourceName);
		Initialize(stream);
	}

	void WicStream::Initialize(String^ fileName, DesiredAccess desiredAccess)
	{
		pin_ptr<const System::Char> pFileName = PtrToStringChars(fileName);
		ComUtils::CheckResult(GetNative()->InitializeFromFilename(pFileName, (DWORD)desiredAccess));
	}

	void WicStream::Initialize(Stream^ stream)
	{
		StreamWrapper ^wrapper = gcnew StreamWrapper(stream);
		IntPtr pStream = Marshal::GetComInterfaceForObject( wrapper, System::Runtime::InteropServices::ComTypes::IStream::typeid );

		ComUtils::CheckResult(GetNative()->InitializeFromIStream((IStream*)pStream.ToPointer()));
	}

	void WicStream::Initialize(Stream^ stream, UInt64 offset, UInt64 maxSize)
	{
		StreamWrapper ^wrapper = gcnew StreamWrapper(stream);
		IntPtr pStream = Marshal::GetComInterfaceForObject( wrapper, System::Runtime::InteropServices::ComTypes::IStream::typeid );
		try
		{
			ComUtils::CheckResult(GetNative()->InitializeFromIStreamRegion(
				(IStream*)pStream.ToPointer(), 
				*(ULARGE_INTEGER *)&offset, 
				*(ULARGE_INTEGER *)&maxSize));
		}
		finally
		{
			Marshal::Release(pStream);
		}
	}

	void WicStream::Initialize(array<Byte>^ buffer)
	{
		if(buffer == nullptr)
			throw gcnew ArgumentNullException("buffer");

		pin_ptr<Byte> pBuffer = &buffer[0];

		ComUtils::CheckResult(GetNative()->InitializeFromMemory((BYTE*)pBuffer, buffer->Length));
	}
}}}