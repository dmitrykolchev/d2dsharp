/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#include "WicCommon.h"

namespace Managed { namespace Graphics { namespace Imaging
{
	public enum class ColorSpace
	{
		Unknown = 0,
		Standard = 1,
		Adobe = 2
	};

	public enum class ColorContextType
	{
		Uninitialized = 0,
		Profile = 1,
		ExifColorSpace = 2
	};

	public ref class WicColorContext: ComWrapper
	{
	internal:
		WicColorContext(IWICColorContext* native): ComWrapper(native)
		{
		}
	public:
		property ColorSpace ExifColorSpace
		{
			ColorSpace get()
			{
				UINT colorSpace;
				ComUtils::CheckResult(GetNative<IWICColorContext>()->GetExifColorSpace(&colorSpace));
				switch(colorSpace)
				{
				case 1: return ColorSpace::Standard;
				case 2: return ColorSpace::Adobe;
				}
				return ColorSpace::Unknown;
			}
		}

		array<Byte>^ GetProfileBytes();

		property ColorContextType ContextType
		{
			ColorContextType get()
			{
				ColorContextType contextType;
				ComUtils::CheckResult(GetNative<IWICColorContext>()->GetType((WICColorContextType*) &contextType));
				return contextType;
			}
		}

		void Initialize(ColorSpace colorSpace)
		{
			if(colorSpace == ColorSpace::Unknown)
				throw gcnew ArgumentOutOfRangeException();
			ComUtils::CheckResult(GetNative<IWICColorContext>()->InitializeFromExifColorSpace((UINT) colorSpace));
		}
		
		void Initialize(String^ fileName)
		{
			pin_ptr<const System::Char> pFileName = PtrToStringChars(fileName);
			ComUtils::CheckResult(GetNative<IWICColorContext>()->InitializeFromFilename(pFileName));
		}
		
		void Initialize(array<Byte>^ buffer)
		{
			if(buffer == nullptr)
				throw gcnew ArgumentNullException();
			UINT length = buffer->Length;
			pin_ptr<Byte> pBuffer = &buffer[0];
			ComUtils::CheckResult(GetNative<IWICColorContext>()->InitializeFromMemory(pBuffer, length));
		}
	};
}}}