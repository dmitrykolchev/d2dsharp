#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	ref class FontFileStream;

	public ref class FontFileLoader: ComWrapper
	{
	internal:
		FontFileLoader(IDWriteFontFileLoader* native): ComWrapper(native)
		{
		}
	public:
		FontFileStream^ CreateStreamFromKey(array<Byte>^ fontFileReferenceKey);
	};
}}}