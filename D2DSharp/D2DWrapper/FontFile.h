#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class FontFile: ComWrapper
	{
	internal:
		FontFile(IDWriteFontFile* native): ComWrapper(native)
		{
		}
	public:
		Boolean Analyze([Out]FontFileType% fontFileType, [Out]FontFaceType% fontFaceType, [Out]UInt32% numberOfFaces);
		FontFileLoader^ GetLoader();
		array<Byte>^ GetReferenceKey();
	internal:
		IDWriteFontFile* GetNative() new 
		{
			return (IDWriteFontFile*)ComWrapper::GetNative();
		}
	};
}}}