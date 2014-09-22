/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "ComWrapper.h"
#include "D2DCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	ref class Direct2DFactory;

	public ref class D2DResource abstract: ComWrapper
	{
	internal:
		D2DResource(ID2D1Resource* native): 
			ComWrapper(native)
		{
		}

	public:
		Direct2DFactory^ GetFactory();
	};
}}}