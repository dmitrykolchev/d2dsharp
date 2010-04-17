/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
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