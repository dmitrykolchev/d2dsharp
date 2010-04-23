#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class FontFileStream: ComWrapper
	{
	internal:
		FontFileStream(IDWriteFontFileStream* native): ComWrapper(native)
		{
		}
	public:
		property UInt64 FileSize
		{
			UInt64 get()
			{
				UINT64 value;
				ComUtils::CheckResult(GetNative()->GetFileSize(&value));
				return value;
			}
		}
		property UInt64 LastWriteTime
		{
			UInt64 get()
			{
				UINT64 value;
				ComUtils::CheckResult(GetNative()->GetLastWriteTime(&value));
				return value;
			}
		}
		//TODO: ReadFileFragment
		//TODO: ReleaseFileFragment
	internal:
		IDWriteFontFileStream* GetNative() new 
		{
			return (IDWriteFontFileStream*)ComWrapper::GetNative();
		}
	};
}}}