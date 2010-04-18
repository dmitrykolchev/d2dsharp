#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;


void FontFace::GetGlyphRunOutline(Single emSize, array<UInt16>^ glyphIndices, array<Single>^ glyphAdvances, 
		array<GlyphOffset>^ glyphOffsets, Boolean isSideways, Boolean isRtl, GeometrySink^ geometrySink)
{
	UINT32 count = glyphIndices->Length;
	pin_ptr<UInt16> pGlyphIndices = &glyphIndices[0];
	pin_ptr<Single> pGlyphAdvances = glyphAdvances == nullptr ? nullptr : &glyphAdvances[0];
	pin_ptr<GlyphOffset> pGlyphOffsets = glyphOffsets == nullptr ? nullptr : &glyphOffsets[0];

	ComUtils::CheckResult(GetNative()->GetGlyphRunOutline(emSize, 
		pGlyphIndices, 
		pGlyphAdvances,
		(DWRITE_GLYPH_OFFSET *)pGlyphOffsets,
		count,
		isSideways,
		isRtl,
		geometrySink->GetNative()));
}

void FontFace::GetGlyphRunOutline(Single emSize, array<UInt16>^ glyphIndices, array<Single>^ glyphAdvances, 
		array<GlyphOffset>^ glyphOffsets, Boolean isSideways, Boolean isRtl, ICustomGeometrySink^ customGeometrySink)
{
	CustomGeometrySink *pSink = new CustomGeometrySink(customGeometrySink);
	try
	{
		UINT32 count = glyphIndices->Length;
		pin_ptr<UInt16> pGlyphIndices = &glyphIndices[0];
		pin_ptr<Single> pGlyphAdvances = glyphAdvances == nullptr ? nullptr : &glyphAdvances[0];
		pin_ptr<GlyphOffset> pGlyphOffsets = glyphOffsets == nullptr ? nullptr : &glyphOffsets[0];

		ComUtils::CheckResult(GetNative()->GetGlyphRunOutline(emSize, 
			pGlyphIndices, 
			pGlyphAdvances,
			(DWRITE_GLYPH_OFFSET *)pGlyphOffsets,
			count,
			isSideways,
			isRtl,
			static_cast<ID2D1GeometrySink*>(pSink)));
	}
	finally
	{
		pSink->Release();
	}
}

