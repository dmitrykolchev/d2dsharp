#pragma once

#include "D2DCommon.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	public ref class Layer: D2DResource
	{
	internal:
		Layer(ID2D1Layer *native): 
			D2DResource(native)
		{
		}
	public:

	internal:
		ID2D1Layer *GetNative() new 
		{
			return (ID2D1Layer *)D2DResource::GetNative();
		}
	};
}}}