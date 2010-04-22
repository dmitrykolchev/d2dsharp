#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	ref class TextAnalysisSource;
	ref class TextAnalysisSink;

	public ref class TextAnalyzer: ComWrapper
	{
	internal:
		TextAnalyzer(IDWriteTextAnalyzer* native): ComWrapper(native)
		{
		}
	public:
		void AnalyzeBidi(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, TextAnalysisSink^ analysisSink);
		void AnalyzeLineBreakpoints(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, TextAnalysisSink^ analysisSink);
		void AnalyzeNumberSubstitution(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, TextAnalysisSink^ analysisSink);
		void AnalyzeScript(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, TextAnalysisSink^ analysisSink);
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