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
#include "TextFormat.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DykBits::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace DirectWrite 
{
	interface class ITextRenderer;
	ref class FontCollection;
	ref class InlineObject;
	ref class Typography;

	[StructLayout(LayoutKind::Sequential)]
	public value struct TextRange
	{
	private:
		UINT32 _startPosition;
		UINT32 _length;
	public:
		TextRange(Int32 startPosition, Int32 length)
		{
			_startPosition = startPosition;
			_length = length;
		}

		property Int32 StartPosition
		{
			Int32 get() { return _startPosition; }
			void set(Int32 value) { _startPosition = value; }
		}

		property Int32 Length
		{
			Int32 get() { return _length; }
			void set(Int32 value) { _length = value; }
		}
	};

	public ref class TextLayout: TextFormat
	{
	internal:
		TextLayout(IDWriteTextLayout* native): 
			TextFormat(native)
		{
		}
	public:
		void Draw(ITextRenderer^ renderer, Single originX, Single originY);
		//array<WriteClusterMetrics>^ GetClusterMetrics();
		property Single MinWidth
		{
			Single get()
			{
				FLOAT minWidth;
				ComUtils::CheckResult(GetNative()->DetermineMinWidth(&minWidth));
				return minWidth;
			}
		}

		property Single MaxHeight
		{
			Single get()
			{
				return GetNative()->GetMaxHeight();
			}
			void set(Single value)
			{
				ComUtils::CheckResult(GetNative()->SetMaxHeight(value));
			}
		}

		property Single MaxWidth
		{
			Single get()
			{
				return GetNative()->GetMaxWidth();
			}
			void set(Single value)
			{
				ComUtils::CheckResult(GetNative()->SetMaxWidth(value));
			}
		}

		Object^ GetDrawingEffect(Int32 position);
		Object^ GetDrawingEffect(Int32 position, [Out]TextRange% textRange);
		FontCollection^ GetFontCollection(Int32 position);
		FontCollection^ GetFontCollection(Int32 position, [Out]TextRange% textRange);
		String^ GetFontFamilyName(Int32 position);
		String^ GetFontFamilyName(Int32 position, [Out]TextRange% textRange);
		Single GetFontSize(Int32 position);
		Single GetFontSize(Int32 position, [Out]TextRange% textRange);
		FontStretch GetFontStretch(Int32 position);
		FontStretch GetFontStretch(Int32 position, [Out]TextRange% textRange);
		FontStyle GetFontStyle(Int32 position);
		FontStyle GetFontStyle(Int32 position, [Out]TextRange% textRange);
		FontWeight GetFontWeight(Int32 position);
		FontWeight GetFontWeight(Int32 position, [Out]TextRange% textRange);
		InlineObject^ GetInlineObject(Int32 position);
		InlineObject^ GetInlineObject(Int32 position, [Out]TextRange% textRange);
		//array<LineMetrics>^ GetLineMetrics();
		System::Globalization::CultureInfo^ TextLayout::GetCultureInfo(Int32 position);
		System::Globalization::CultureInfo^ TextLayout::GetCultureInfo(Int32 position, [Out]TextRange% textRange);
		//TextMetrics GetMetrics();
		//OverhangMetrics GetOverhangMetrics();
		Boolean GetStrikethrough(Int32 position);
		Boolean GetStrikethrough(Int32 position, [Out]TextRange% textRange);
		Typography^ GetTypography(Int32 position);
		Typography^ GetTypography(Int32 position, [Out]TextRange% textRange);
		Boolean GetUnderline(Int32 position);
		Boolean GetUnderline(Int32 position, [Out]TextRange% textRange);
		//HitTestMetrics HitTestPoint(Single x, Single y, [Out]Boolean% isTrailingHit, [Out]Boolean isInside);
		//HitTestMetrics HitTestTextPosition(Int32 textPosition, Boolean isTrailingHit, [Out]Single% pointX, [Out]Single% pointY);
		//array<HitTestMetrics>^ HitTestTextRange(Int32 textPosition, Int32 textLength, Single originX, Single originY);
		void SetDrawingEffect(Object^ drawingEffect, TextRange textRange);
		void SetFontCollection(FontCollection^ fontCollection, TextRange textRange);
		void SetFontFamilyName(String^ fontFamilyName, TextRange textRange);
		void SetFontSize(Single fontSize, TextRange textRange);
		void SetFontStretch(FontStretch fontStretch, TextRange textRange);
		void SetFontStyle(FontStyle fontStyle, TextRange textRange);
		void SetFontWeight(FontWeight fontWeight, TextRange textRange);
		void SetInlineObject(InlineObject^ inlineObject, TextRange textRange);
		void SetCultureInfo(System::Globalization::CultureInfo^ cultureInfo, TextRange textRange);
		void SetStrikethrough(Boolean hasStrikethrough, TextRange textRange);
		void SetTypography(Typography^ typography, TextRange textRange);
		void SetUnderline(Boolean hasUnderline, TextRange textRange);
	internal:
		IDWriteTextLayout* GetNative() new
		{
			return (IDWriteTextLayout*)TextFormat::GetNative();
		}
	};
}}}