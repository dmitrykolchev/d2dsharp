/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"

namespace Managed { namespace Graphics { namespace Direct2D 
{
	public ref class Layer: D2DResource
	{
	internal:
		Layer(ID2D1Layer *native): 
			D2DResource(native)
		{
		}
	public:
	};
}}}