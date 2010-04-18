#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class RenderingParams: ComWrapper
	{
	internal:
		RenderingParams(IDWriteRenderingParams* native): ComWrapper(native)
		{
		}

	internal:
		IDWriteRenderingParams* GetNative() new 
		{
			return (IDWriteRenderingParams*)ComWrapper::GetNative();
		}
	};
}}}