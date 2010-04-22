/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;


void TextAnalyzer::AnalyzeBidi(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, TextAnalysisSink^ analysisSink)
{
	ComUtils::CheckResult(
		GetNative()->AnalyzeBidi(
			analysisSource->GetNative(),
			textPosition, 
			textLength,
			analysisSink->GetNative()));
}

void TextAnalyzer::AnalyzeLineBreakpoints(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, TextAnalysisSink^ analysisSink)
{
	IDWriteTextAnalysisSource * source = analysisSource->GetNative();
	IDWriteTextAnalysisSink * sink = analysisSink->GetNative();

	ComUtils::CheckResult(
		GetNative()->AnalyzeLineBreakpoints(
			source,
			textPosition, 
			textLength,
			sink));
			
}

void TextAnalyzer::AnalyzeNumberSubstitution(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, TextAnalysisSink^ analysisSink)
{
	ComUtils::CheckResult(
		GetNative()->AnalyzeNumberSubstitution(
			analysisSource->GetNative(),
			textPosition, 
			textLength,
			analysisSink->GetNative()));
}

void TextAnalyzer::AnalyzeScript(TextAnalysisSource^ analysisSource, UInt32 textPosition, UInt32 textLength, TextAnalysisSink^ analysisSink)
{
	ComUtils::CheckResult(
		GetNative()->AnalyzeScript(
			analysisSource->GetNative(),
			textPosition, 
			textLength,
			analysisSink->GetNative()));
}
