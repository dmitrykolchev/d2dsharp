/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Graphics::DirectWrite;

GlyphRun::GlyphRun(DWRITE_GLYPH_RUN const* glyphRun)
{
	_fontFace = gcnew Managed::Graphics::DirectWrite::FontFace(glyphRun->fontFace, true);
	_fontEmSize = glyphRun->fontEmSize;
	UINT32 count = glyphRun->glyphCount;
	_glyphCount = (Int32)count;

	array<UInt16>^ indices = gcnew array<UInt16>(count);
	pin_ptr<UInt16> pIndices = &indices[0];
	memcpy(pIndices, glyphRun->glyphIndices, count * sizeof(UINT16));
	_glyphIndices = indices;

	array<Single>^ advances = gcnew array<Single>(count);
	pin_ptr<Single> pAdvances = &advances[0];
	memcpy(pAdvances, glyphRun->glyphAdvances, count * sizeof(FLOAT));
	_glyphAdvances = advances;

	array<GlyphOffset>^ offsets = gcnew array<GlyphOffset>(count);
	pin_ptr<GlyphOffset> pOffsets = &offsets[0];
	memcpy(pOffsets, glyphRun->glyphOffsets, count * sizeof(DWRITE_GLYPH_OFFSET));
	_glyphOffsets = offsets;

	_isSideways = glyphRun->isSideways != 0;
	_bidiLevel = glyphRun->bidiLevel;
}

void GlyphRun::CopyTo(DWRITE_GLYPH_RUN* glyphRun)
{
	// TODO: complete method

	glyphRun->fontFace = _fontFace->GetNative();
	glyphRun->fontEmSize = _fontEmSize;
	glyphRun->glyphCount = _glyphIndices->Length;

	glyphRun->isSideways = _isSideways;
	glyphRun->bidiLevel = _bidiLevel;
	
	throw gcnew NotImplementedException();
}

GlyphRun::!GlyphRun()
{
	if(_fontFace != nullptr)
		delete _fontFace;
}

GlyphRunDescription::GlyphRunDescription(DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription)
{
	_localeName = gcnew System::String(glyphRunDescription->localeName);
	UINT32 count = glyphRunDescription->stringLength;
	_string = gcnew System::String(glyphRunDescription->string, 0, count);
	array<UInt16>^ clusterMap = gcnew array<UInt16>(count);
	pin_ptr<UInt16> pClusterMap = &clusterMap[0];
	memcpy(pClusterMap, glyphRunDescription->clusterMap, count * sizeof(UINT16));
	_clusterMap = clusterMap;
	_textPosition = glyphRunDescription->textPosition;
}

Underline::Underline(DWRITE_UNDERLINE const* underline)
{
	_width = underline->width;
	_thickness = underline->thickness;
	_offset = underline->offset;
	_runHeight = underline->runHeight;
	_readingDirection = (Managed::Graphics::DirectWrite::ReadingDirection)underline->readingDirection;
	_flowDirection = (Managed::Graphics::DirectWrite::FlowDirection)underline->flowDirection;
	_localeName = gcnew System::String(underline->localeName);
	_measuringMode = (Managed::Graphics::Direct2D::MeasuringMode)underline->measuringMode;
}

Strikethrough::Strikethrough(DWRITE_STRIKETHROUGH const* strikethrough)
{
	_width = strikethrough->width;
	_thickness = strikethrough->thickness;
	_offset = strikethrough->offset;
	_readingDirection = (Managed::Graphics::DirectWrite::ReadingDirection)strikethrough->readingDirection;
	_flowDirection = (Managed::Graphics::DirectWrite::FlowDirection)strikethrough->flowDirection;
	_localeName = gcnew System::String(strikethrough->localeName);
	_measuringMode = (Managed::Graphics::Direct2D::MeasuringMode)strikethrough->measuringMode;
}