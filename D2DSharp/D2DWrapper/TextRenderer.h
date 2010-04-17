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
using namespace DykBits::Graphics::Direct2D;

namespace DykBits { namespace Graphics { namespace DirectWrite 
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