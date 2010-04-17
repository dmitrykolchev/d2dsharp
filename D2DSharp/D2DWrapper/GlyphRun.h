/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
* Copyright (C) 2010 Dmitry Kolchev
*
* This sourcecode is licenced under The GNU Lesser General Public License
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
* NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
* USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

#include "ComWrapper.h"
#include "ComUtils.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DykBits::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace DirectWrite 
{
	public value struct GlyphOffset
	{
	private:
		Single _advanceOffset;
		Single _ascenderOffset;
	public:
		GlyphOffset(Single advanceOffset, Single ascenderOffset)
		{
			_advanceOffset = advanceOffset;
			_ascenderOffset = ascenderOffset;
		}

		property Single AdvanceOffset { Single get() { return _advanceOffset; } }
		property Single AscenderOffset { Single get() { return _ascenderOffset; } }
	};

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
	public:
		property DykBits::Graphics::DirectWrite::FontFace^ FontFace
		{
			DykBits::Graphics::DirectWrite::FontFace^ get() { return _fontFace; }
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
		DykBits::Graphics::Direct2D::MeasuringMode _measuringMode;
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
		property DykBits::Graphics::DirectWrite::ReadingDirection ReadingDirection
		{
			DykBits::Graphics::DirectWrite::ReadingDirection get() { return _readingDirection; }
		}
		property DykBits::Graphics::DirectWrite::FlowDirection FlowDirection
		{
			DykBits::Graphics::DirectWrite::FlowDirection get() { return _flowDirection; }
		}
		property String^ LocaleName
		{
			String^ get() { return _localeName; }
		}
		property DykBits::Graphics::Direct2D::MeasuringMode MeasuringMode
		{
			DykBits::Graphics::Direct2D::MeasuringMode get() { return _measuringMode; }
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
		DykBits::Graphics::Direct2D::MeasuringMode _measuringMode;
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
		property DykBits::Graphics::DirectWrite::ReadingDirection ReadingDirection
		{
			DykBits::Graphics::DirectWrite::ReadingDirection get() { return _readingDirection; }
		}
		property DykBits::Graphics::DirectWrite::FlowDirection FlowDirection
		{
			DykBits::Graphics::DirectWrite::FlowDirection get() { return _flowDirection; }
		}
		property String^ LocaleName
		{
			String^ get() { return _localeName; }
		}
		property DykBits::Graphics::Direct2D::MeasuringMode MeasuringMode
		{
			DykBits::Graphics::Direct2D::MeasuringMode get() { return _measuringMode; }
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