/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "ComWrapper.h"
#include "ComUtils.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class TextAnalysisSource abstract
	{
	public:
		System::Globalization::CultureInfo^ GetCulture(UInt32 testPosition, [Out]UInt32% textLength)
		{
			throw new NotImplementedException();
		}
		NumberSubstitution^ GetNumberSubstitution(UInt32 testPosition, [Out]UInt32% textLength)
		{
			throw new NotImplementedException();
		}

		property Managed::Graphics::DirectWrite::ReadingDirection ReadingDirection 
		{
			Managed::Graphics::DirectWrite::ReadingDirection get()
			{
				throw new NotImplementedException();
			}
		}

	};

}}}