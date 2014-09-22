/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"
#include "TessellationSink.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	public ref class Mesh: D2DResource
	{
	internal:
		Mesh(ID2D1Mesh *native): 
			D2DResource(native)
		{
		}
	public:
		TessellationSink^ Open()
		{
			ID2D1TessellationSink *tessellationSink;
			ComUtils::CheckResult(GetNative<ID2D1Mesh>()->Open(&tessellationSink));
			return gcnew TessellationSink(tessellationSink);
		}
	};
}}}