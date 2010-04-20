#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class TextAnalyzer: ComWrapper
	{
	internal:
		TextAnalyzer(IDWriteTextAnalyzer* native): ComWrapper(native)
		{
		}
	public:
		//void AnalyzeBidi(ITextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, ITextAnalysisSink^ analysisSink);
		//void AnalyzeBreakpoints(ITextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, ITextAnalysisSink^ analysisSink);
		//void AnalyzeNumberSubstitution(ITextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, ITextAnalysisSink^ analysisSink);
		//void AnalyzeScript(ITextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, ITextAnalysisSink^ analysisSink);
		//void GetGdiCompatibleGlyphPlacements
		//void GetGlyphPlacements
		//void GetGlyphs
	internal:
		IDWriteTextAnalyzer* GetNative() new 
		{
			return (IDWriteTextAnalyzer*)ComWrapper::GetNative();
		}
	};
}}}