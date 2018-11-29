/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DResource.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	[System::Security::SuppressUnmanagedCodeSecurity]
	public ref class GradientStopCollection: D2DResource
	{
	internal:
		GradientStopCollection(ID2D1GradientStopCollection *native): 
			D2DResource(native)
		{
		}
	};
}}}