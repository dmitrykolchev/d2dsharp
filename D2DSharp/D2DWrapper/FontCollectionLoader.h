#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class FontCollectionLoader: ComWrapper
	{
	internal:
		FontCollectionLoader(IDWriteFontCollectionLoader* native): ComWrapper(native)
		{
		}

	internal:
		IDWriteFontCollectionLoader* GetNative() new 
		{
			return (IDWriteFontCollectionLoader*)ComWrapper::GetNative();
		}
	};
}}}