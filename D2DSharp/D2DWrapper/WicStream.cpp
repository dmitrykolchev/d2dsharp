/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicStream.h"


namespace Managed { namespace Graphics { namespace Imaging
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