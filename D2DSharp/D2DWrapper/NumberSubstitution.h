#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class NumberSubstitution: ComWrapper
	{
	internal:
		NumberSubstitution(IDWriteNumberSubstitution* native): ComWrapper(native)
		{
		}
	};
}}}