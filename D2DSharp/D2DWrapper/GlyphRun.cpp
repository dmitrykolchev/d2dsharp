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
#include "Stdafx.h"

#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DykBits::Graphics::DirectWrite;

GlyphRun::GlyphRun(DWRITE_GLYPH_RUN const* glyphRun)
{
	_fontFace = gcnew DykBits::Graphics::DirectWrite::FontFace(glyphRun->fontFace, true);
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
	_readingDirection = (DykBits::Graphics::DirectWrite::ReadingDirection)underline->readingDirection;
	_flowDirection = (DykBits::Graphics::DirectWrite::FlowDirection)underline->flowDirection;
	_localeName = gcnew System::String(underline->localeName);
	_measuringMode = (DykBits::Graphics::Direct2D::MeasuringMode)underline->measuringMode;
}

Strikethrough::Strikethrough(DWRITE_STRIKETHROUGH const* strikethrough)
{
	_width = strikethrough->width;
	_thickness = strikethrough->thickness;
	_offset = strikethrough->offset;
	_readingDirection = (DykBits::Graphics::DirectWrite::ReadingDirection)strikethrough->readingDirection;
	_flowDirection = (DykBits::Graphics::DirectWrite::FlowDirection)strikethrough->flowDirection;
	_localeName = gcnew System::String(strikethrough->localeName);
	_measuringMode = (DykBits::Graphics::Direct2D::MeasuringMode)strikethrough->measuringMode;
}