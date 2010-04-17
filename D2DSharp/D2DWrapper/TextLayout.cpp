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

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DykBits::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace DirectWrite 
{
	void TextLayout::Draw(ITextRenderer^ renderer, Single originX, Single originY)
	{
		CustomTextRenderer* customRenderer = new CustomTextRenderer(renderer);
		customRenderer->AddRef();
		try
		{
			ComUtils::CheckResult(GetNative()->Draw(NULL, (IDWriteTextRenderer*)customRenderer, originX, originY));
		}
		finally
		{
			customRenderer->Release();
		}
	}

	//WriteClusterMetrics[] GetClusterMetrics()

	Object^ TextLayout::GetDrawingEffect(Int32 position)
	{
		throw gcnew NotImplementedException();
	}

	Object^ TextLayout::GetDrawingEffect(Int32 position, [Out]TextRange% textRange)
	{
		throw gcnew NotImplementedException();
	}

	FontCollection^ TextLayout::GetFontCollection(Int32 position)
	{
		IDWriteFontCollection* fontCollection;
		ComUtils::CheckResult(GetNative()->GetFontCollection(position, &fontCollection, NULL));
		return gcnew FontCollection(fontCollection);
	}

	FontCollection^ TextLayout::GetFontCollection(Int32 position, [Out]TextRange% textRange)
	{
		IDWriteFontCollection* fontCollection;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetFontCollection(position, &fontCollection, (DWRITE_TEXT_RANGE *)pTextRange));
		return gcnew FontCollection(fontCollection);
	}

	String^ TextLayout::GetFontFamilyName(Int32 position)
	{
		IDWriteTextLayout* native = GetNative();
		UINT32 nameLength;
		ComUtils::CheckResult(native->GetFontFamilyNameLength(position, &nameLength, NULL));
		wchar_t* name = new wchar_t[nameLength + 1];
		try
		{
			ComUtils::CheckResult(native->GetFontFamilyName(position, name, nameLength, NULL));
			return gcnew String(name);
		}
		finally
		{
			delete name;
		}
	}

	String^ TextLayout::GetFontFamilyName(Int32 position, [Out]TextRange% textRange)
	{
		IDWriteTextLayout* native = GetNative();
		UINT32 nameLength;
		ComUtils::CheckResult(native->GetFontFamilyNameLength(position, &nameLength, NULL));
		wchar_t* name = new wchar_t[nameLength + 1];
		try
		{
			pin_ptr<TextRange> pTextRange = &textRange;
			ComUtils::CheckResult(native->GetFontFamilyName(position, name, nameLength, (DWRITE_TEXT_RANGE *)pTextRange));
			return gcnew String(name);
		}
		finally
		{
			delete name;
		}
	}

	Single TextLayout::GetFontSize(Int32 position)
	{
		FLOAT fontSize;
		ComUtils::CheckResult(GetNative()->GetFontSize(position, &fontSize, NULL));
		return fontSize;
	}

	Single TextLayout::GetFontSize(Int32 position, [Out]TextRange% textRange)
	{
		FLOAT fontSize;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetFontSize(position, &fontSize, (DWRITE_TEXT_RANGE *)pTextRange));
		return fontSize;
	}

	FontStretch TextLayout::GetFontStretch(Int32 position)
	{
		DWRITE_FONT_STRETCH value;
		ComUtils::CheckResult(GetNative()->GetFontStretch(position, &value, NULL));
		return (FontStretch)value;
	}

	FontStretch TextLayout::GetFontStretch(Int32 position, [Out]TextRange% textRange)
	{
		DWRITE_FONT_STRETCH value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetFontStretch(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return (FontStretch)value;
	}

	FontStyle TextLayout::GetFontStyle(Int32 position)
	{
		DWRITE_FONT_STYLE value;
		ComUtils::CheckResult(GetNative()->GetFontStyle(position, &value, NULL));
		return (FontStyle)value;
	}

	FontStyle TextLayout::GetFontStyle(Int32 position, [Out]TextRange% textRange)
	{
		DWRITE_FONT_STYLE value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetFontStyle(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return (FontStyle)value;
	}

	FontWeight TextLayout::GetFontWeight(Int32 position)
	{
		DWRITE_FONT_WEIGHT value;
		ComUtils::CheckResult(GetNative()->GetFontWeight(position, &value, NULL));
		return (FontWeight)value;
	}

	FontWeight TextLayout::GetFontWeight(Int32 position, [Out]TextRange% textRange)
	{
		DWRITE_FONT_WEIGHT value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetFontWeight(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return (FontWeight)value;
	}

	InlineObject^ TextLayout::GetInlineObject(Int32 position)
	{
		IDWriteInlineObject * value;
		ComUtils::CheckResult(GetNative()->GetInlineObject(position, &value, NULL));
		return gcnew InlineObject(value);
	}

	InlineObject^ TextLayout::GetInlineObject(Int32 position, [Out]TextRange% textRange)
	{
		IDWriteInlineObject * value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetInlineObject(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return gcnew InlineObject(value);
	}

	//array<LineMetrics>^ TextLayout::GetLineMetrics()

	System::Globalization::CultureInfo^ TextLayout::GetCultureInfo(Int32 position)
	{
		UINT32 len;
		ComUtils::CheckResult(GetNative()->GetLocaleNameLength(position, &len));
		wchar_t* name = new wchar_t[len + 1];
		try
		{        
			ComUtils::CheckResult(GetNative()->GetLocaleName(position, name, len, NULL));
			return gcnew System::Globalization::CultureInfo(gcnew String(name));
		}
		finally
		{
			delete [] name;
		}
	}

	System::Globalization::CultureInfo^ TextLayout::GetCultureInfo(Int32 position, [Out]TextRange% textRange)
	{
		UINT32 len;
		ComUtils::CheckResult(GetNative()->GetLocaleNameLength(position, &len));
		wchar_t* name = new wchar_t[len + 1];
		try
		{        
			pin_ptr<TextRange> pTextRange = &textRange;
			ComUtils::CheckResult(GetNative()->GetLocaleName(position, name, len, (DWRITE_TEXT_RANGE *)pTextRange));
			return gcnew System::Globalization::CultureInfo(gcnew String(name));
		}
		finally
		{
			delete [] name;
		}
	}

	//TextMetrics TextLayout::GetMetrics()

	//OverhangMetrics TextLayout::GetOverhangMetrics()

	Boolean TextLayout::GetStrikethrough(Int32 position)
	{
		BOOL value;
		ComUtils::CheckResult(GetNative()->GetStrikethrough(position, &value, NULL));
		return value != 0;
	}

	Boolean TextLayout::GetStrikethrough(Int32 position, [Out]TextRange% textRange)
	{
		BOOL value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetStrikethrough(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return value != 0;
	}

	Typography^ TextLayout::GetTypography(Int32 position)
	{
		IDWriteTypography* value;
		ComUtils::CheckResult(GetNative()->GetTypography(position, &value, NULL));
		return gcnew Typography(value);
	}

	Typography^ TextLayout::GetTypography(Int32 position, [Out]TextRange% textRange)
	{
		IDWriteTypography* value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetTypography(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return gcnew Typography(value);
	}

	Boolean TextLayout::GetUnderline(Int32 position)
	{
		BOOL value;
		ComUtils::CheckResult(GetNative()->GetUnderline(position, &value, NULL));
		return value != 0;
	}

	Boolean TextLayout::GetUnderline(Int32 position, [Out]TextRange% textRange)
	{
		BOOL value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetUnderline(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return value != 0;
	}

	//HitTestMetrics TextLayout::HitTestPoint(Single x, Single y, [Out]Boolean% isTrailingHit, [Out]Boolean isInside)
	//HitTestMetrics TextLayout::HitTestTextPosition(Int32 textPosition, Boolean isTrailingHit, [Out]Single% pointX, [Out]Single% pointY)
	//array<HitTestMetrics>^ TextLayout::HitTestTextRange(Int32 textPosition, Int32 textLength, Single originX, Single originY)
	void TextLayout::SetDrawingEffect(Object^ drawingEffect, TextRange textRange)
	{
		throw gcnew NotImplementedException();
	}

	void TextLayout::SetFontCollection(FontCollection^ fontCollection, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetFontCollection(fontCollection->GetNative(), *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetFontFamilyName(String^ fontFamilyName, TextRange textRange)
	{
		pin_ptr<const wchar_t> name = PtrToStringChars(fontFamilyName);
		ComUtils::CheckResult(GetNative()->SetFontFamilyName(name, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetFontSize(Single fontSize, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetFontSize(fontSize, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetFontStretch(FontStretch fontStretch, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetFontStretch((DWRITE_FONT_STRETCH)fontStretch, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetFontStyle(FontStyle fontStyle, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetFontStyle((DWRITE_FONT_STYLE)fontStyle, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetFontWeight(FontWeight fontWeight, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetFontWeight((DWRITE_FONT_WEIGHT)fontWeight, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetInlineObject(InlineObject^ inlineObject, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetInlineObject(inlineObject->GetNative(), *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetCultureInfo(System::Globalization::CultureInfo^ cultureInfo, TextRange textRange)
	{
		pin_ptr<const wchar_t> name = PtrToStringChars(cultureInfo->Name);
		ComUtils::CheckResult(GetNative()->SetLocaleName(name, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetStrikethrough(Boolean hasStrikethrough, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetStrikethrough(hasStrikethrough, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetTypography(Typography^ typography, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetTypography(typography->GetNative(), *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetUnderline(Boolean hasUnderline, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetUnderline(hasUnderline, *(DWRITE_TEXT_RANGE *)&textRange));
	}

}}}