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
		void AnalyzeBidi(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength);
		void AnalyzeLineBreakpoints(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength);
		void AnalyzeNumberSubstitution(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength);
		void AnalyzeScript(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength);
		//void GetGdiCompatibleGlyphPlacements
		//void GetGlyphPlacements
		UInt32 GetGlyphs(
			String^ textString, 
			FontFace^ fontFace, 
			Boolean isSideways, 
			Boolean isRightToLeft, 
			ScriptAnalysis scriptAnalysis, 
			System::Globalization::CultureInfo^ culture, 
			NumberSubstitution^ numberSubstitution, 
			array<array<FontFeature>^>^ features,
			array<UInt16>^ clusterMap,
			array<ShapingTextProperties>^ textProps, 
			array<UInt16>^ glyphIndices, 
			array<ShapingGlyphProperties>^ glyphProps);

	internal:
		IDWriteTextAnalyzer* GetNative() new 
		{
			return (IDWriteTextAnalyzer*)ComWrapper::GetNative();
		}
	};
}}}