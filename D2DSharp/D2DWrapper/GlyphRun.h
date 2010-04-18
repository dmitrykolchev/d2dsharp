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

	ref class FontFace;

	public ref class GlyphRun
	{
	private:
		FontFace^ _fontFace;
		Single _fontEmSize;
		Int32 _glyphCount;
		array<UInt16>^ _glyphIndices;
		array<Single>^ _glyphAdvances;
		array<GlyphOffset>^ _glyphOffsets;
		Boolean _isSideways;
		Int32 _bidiLevel;
	internal:
		GlyphRun(DWRITE_GLYPH_RUN const* glyphRun);
		~GlyphRun()
		{
			this->!GlyphRun();
		}
		!GlyphRun();
		void CopyTo(DWRITE_GLYPH_RUN* glyphRun);
	public:
		property Managed::Graphics::DirectWrite::FontFace^ FontFace
		{
			Managed::Graphics::DirectWrite::FontFace^ get() { return _fontFace; }
		}

		property Single EmSize
		{
			Single get() { return _fontEmSize; }
		}

		property Int32 GlyphCount
		{
			Int32 get() { return _glyphCount; }
		}

		property array<UInt16>^ GlyphIndices
		{
			array<UInt16>^ get() { return _glyphIndices; }
		}

		property array<Single>^ GlyphAdvances
		{
			array<Single>^ get() { return _glyphAdvances; }
		}

		property array<GlyphOffset>^ GlyphOffsets
		{
			array<GlyphOffset>^ get() { return _glyphOffsets; }
		}

		property Boolean IsSideways
		{
			Boolean get() { return _isSideways; }
		}

		property Int32 BidiLevel
		{
			Int32 get() { return _bidiLevel; }
		}
	};

	public ref class Underline
	{
	private:
		Single _width;
		Single _thickness;
		Single _offset;
		Single _runHeight;
		ReadingDirection _readingDirection;
		FlowDirection _flowDirection;
		String^ _localeName;
		Managed::Graphics::Direct2D::MeasuringMode _measuringMode;
	public:
		Underline(DWRITE_UNDERLINE const* underline);

		property Single Width 
		{ 
			Single get() { return _width; }
		}
		property Single Thickness
		{
			Single get() { return _thickness; }
		}
		property Single Offset
		{
			Single get() { return _offset; }
		}
		property Single RunHeight
		{
			Single get() { return _runHeight; }
		}
		property Managed::Graphics::DirectWrite::ReadingDirection ReadingDirection
		{
			Managed::Graphics::DirectWrite::ReadingDirection get() { return _readingDirection; }
		}
		property Managed::Graphics::DirectWrite::FlowDirection FlowDirection
		{
			Managed::Graphics::DirectWrite::FlowDirection get() { return _flowDirection; }
		}
		property String^ LocaleName
		{
			String^ get() { return _localeName; }
		}
		property Managed::Graphics::Direct2D::MeasuringMode MeasuringMode
		{
			Managed::Graphics::Direct2D::MeasuringMode get() { return _measuringMode; }
		}
	};

	public ref class Strikethrough
	{
	private:
		Single _width;
		Single _thickness;
		Single _offset;
		ReadingDirection _readingDirection;
		FlowDirection _flowDirection;
		String^ _localeName;
		Managed::Graphics::Direct2D::MeasuringMode _measuringMode;
	public:
		Strikethrough(DWRITE_STRIKETHROUGH const* strikethrough);

		property Single Width 
		{ 
			Single get() { return _width; }
		}
		property Single Thickness
		{
			Single get() { return _thickness; }
		}
		property Single Offset
		{
			Single get() { return _offset; }
		}
		property Managed::Graphics::DirectWrite::ReadingDirection ReadingDirection
		{
			Managed::Graphics::DirectWrite::ReadingDirection get() { return _readingDirection; }
		}
		property Managed::Graphics::DirectWrite::FlowDirection FlowDirection
		{
			Managed::Graphics::DirectWrite::FlowDirection get() { return _flowDirection; }
		}
		property String^ LocaleName
		{
			String^ get() { return _localeName; }
		}
		property Managed::Graphics::Direct2D::MeasuringMode MeasuringMode
		{
			Managed::Graphics::Direct2D::MeasuringMode get() { return _measuringMode; }
		}
	};

	public ref class GlyphRunDescription
	{
	private:
		System::String^ _localeName;
		System::String^ _string;
		array<UInt16>^ _clusterMap;
		Int32 _textPosition;
	internal:
		GlyphRunDescription(DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription);
	public:
		property System::String^ LocaleName 
		{ 
			System::String^ get() { return _localeName; }
		}

		property System::String^ String
		{
			System::String^ get() { return _string; }
		}

		property array<UInt16>^ ClusterMap
		{
			array<UInt16>^ get() { return _clusterMap; }
		}

		property Int32 TextPosition
		{
			Int32 get() { return _textPosition; }
		}
	};

}}}