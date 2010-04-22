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


UInt32 TextAnalyzer::GetGlyphs(
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
	array<ShapingGlyphProperties>^ glyphProps)
{
	pin_ptr<const wchar_t> pTextString = PtrToStringChars(textString);
	pin_ptr<const wchar_t> pLocaleName = PtrToStringChars(culture->Name);

	IDWriteTextAnalyzer *native = GetNative();
	IDWriteFontFace *pFontFace = fontFace->GetNative();
	IDWriteNumberSubstitution* pNumberSubstitution = numberSubstitution->GetNative();

	UINT32 featureRanges = features->Length;
	UINT32* featureRangeLengths = new UINT32[featureRanges];
	DWRITE_TYPOGRAPHIC_FEATURES ** pFeatures = new DWRITE_TYPOGRAPHIC_FEATURES*[featureRanges];

	for(UINT32 index = 0; index < featureRanges; ++index)
	{
		array<FontFeature>^ featureRange = features[index];
		featureRangeLengths[index] = featureRange->Length;
		pFeatures[index] = new DWRITE_TYPOGRAPHIC_FEATURES();
		pFeatures[index]->features = new DWRITE_FONT_FEATURE[featureRange->Length];
		for(int ff = 0; ff < featureRange->Length; ++ff)
		{
			pFeatures[index]->features[ff].nameTag = (DWRITE_FONT_FEATURE_TAG)featureRange[ff].NameTag;
			pFeatures[index]->features[ff].parameter = featureRange[ff].Parameter;
		}
	}

	pin_ptr<UInt16> pClusterMap = &clusterMap[0];
	pin_ptr<ShapingTextProperties> pTextProps = &textProps[0];
	pin_ptr<UInt16> pGlyphIndices = &glyphIndices[0];
	pin_ptr<ShapingGlyphProperties> pGlyphProps = &glyphProps[0];

	UINT32 count;

	native->GetGlyphs(
		pTextString,
		textString->Length,
		pFontFace,
		isSideways,
		isRightToLeft,
		(DWRITE_SCRIPT_ANALYSIS*)&scriptAnalysis,
		pLocaleName,
		pNumberSubstitution,
		(const DWRITE_TYPOGRAPHIC_FEATURES **)pFeatures,
		featureRangeLengths,
		featureRanges,
		clusterMap->Length,
		pClusterMap,
		(DWRITE_SHAPING_TEXT_PROPERTIES *)pTextProps,
		pGlyphIndices,
		(DWRITE_SHAPING_GLYPH_PROPERTIES *)pGlyphProps,
		&count);


	return count;
}
