#pragma once

#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	ref class NumberSubstitution;

	public interface class ITextAnalysisSource
	{
	public:
		//System::Globalization::CultureInfo^ GetCulture(UInt32 textPosition, UInt32 textLength);
		//NumberSubstitution^ GetNumberSubstitution(UInt32 textPosition, UInt32 textLength);
		//property ReadingDirection ParagraphReadingDirection
		//{
		//	ReadingDirection get();
		//}


	};
}}}