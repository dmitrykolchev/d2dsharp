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
using namespace Managed::Graphics::Direct2D;

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	ref class GlyphRun;
	ref class GlyphRunDescription;
	ref class Underline;
	ref class Strikethrough;

	public interface class ITextRenderer
	{
	public:
		property Boolean IsPixelSnappingDisabled { Boolean get() = 0; }
		
		property Matrix3x2 CurrentTransform { Matrix3x2 get() = 0; }
		
		property Single PixelsPerDip { Single get() = 0; }
		
		void DrawGlyphRun(Single baselineOriginX, Single baselineOriginY, MeasuringMode measuringMode, 
			GlyphRun^ glyphRun, GlyphRunDescription^ glyphRunDescription, Object^ clientDrawingEffect);
		
		void DrawUnderline(Single baselineOriginX, Single baselineOriginY, 
			Underline^ underline, Object^ clientDrawingEffect);

		void DrawStrikethrough(Single baselineOriginX, Single baselineOriginY, 
			Strikethrough^ strikethrough, Object^ clientDrawingEffect);

		void DrawInlineObject(Single originX, Single originY, InlineObject^ inlineObject, 
			Boolean isSideways, Boolean isRightToLeft, Object^ clientDrawingEffect);
	};
}}}