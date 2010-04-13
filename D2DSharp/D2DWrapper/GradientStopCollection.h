#pragma once

#include "D2DResource.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class GradientStopCollection: D2DResource
	{
	internal:
		GradientStopCollection(ID2D1GradientStopCollection *native): 
			D2DResource(native)
		{
		}

		ID2D1GradientStopCollection *GetNative()
		{
			return (ID2D1GradientStopCollection *)D2DResource::GetNative();
		}
	};
}}}