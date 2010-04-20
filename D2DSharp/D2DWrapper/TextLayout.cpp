/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	void TextLayout::Draw(ITextRenderer^ renderer, Single originX, Single originY)
	{
		CustomTextRenderer* customRenderer = new CustomTextRenderer(renderer);
		try
		{
			ComUtils::CheckResult(GetNative()->Draw(NULL, static_cast<IDWriteTextRenderer*>(customRenderer), originX, originY));
		}
		finally
		{
			customRenderer->Release();
		}
	}

	array<Managed::Graphics::DirectWrite::ClusterMetrics>^ TextLayout::ClusterMetrics::get()
	{
		UINT32 count;
		HRESULT hr = GetNative()->GetClusterMetrics(NULL, 0, &count);
		if(FAILED(hr) && hr != E_NOT_SUFFICIENT_BUFFER)
			Marshal::ThrowExceptionForHR(hr);
		array<Managed::Graphics::DirectWrite::ClusterMetrics>^ metrics = gcnew array<Managed::Graphics::DirectWrite::ClusterMetrics>(count);
		pin_ptr<Managed::Graphics::DirectWrite::ClusterMetrics> pMetrics = &metrics[0];
		ComUtils::CheckResult(GetNative()->GetClusterMetrics((DWRITE_CLUSTER_METRICS *)pMetrics, count, &count));
		return metrics;
	}

	ClientDrawingEffect^ TextLayout::GetDrawingEffect(Int32 position)
	{
		IUnknown* drawingEffect;
		ComUtils::CheckResult(GetNative()->GetDrawingEffect(position, &drawingEffect, NULL));

		if(drawingEffect)
		{
			try
			{
				ClientDrawingEffectNative* native;

				ComUtils::CheckResult(drawingEffect->QueryInterface(__uuidof(ClientDrawingEffectNative), (void**)&native));

				return native->GetObject();
			}
			finally
			{
				if(drawingEffect)
					drawingEffect->Release();
			}
		}
		return nullptr;
	}

	ClientDrawingEffect^ TextLayout::GetDrawingEffect(Int32 position, [Out]TextRange% textRange)
	{
		IUnknown* drawingEffect;

		pin_ptr<TextRange> pTextRange = &textRange;

		ComUtils::CheckResult(GetNative()->GetDrawingEffect(position, &drawingEffect, (DWRITE_TEXT_RANGE *)pTextRange));

		if(drawingEffect)
		{
			try
			{
				ClientDrawingEffectNative* native;

				ComUtils::CheckResult(drawingEffect->QueryInterface(__uuidof(ClientDrawingEffectNative), (void**)&native));

				return native->GetObject();
			}
			finally
			{
				if(drawingEffect)
					drawingEffect->Release();
			}
		}
		return nullptr;
	}

	void TextLayout::SetDrawingEffect(ClientDrawingEffect^ drawingEffect, TextRange textRange)
	{
		if(drawingEffect == nullptr)
		{
			ComUtils::CheckResult(GetNative()->SetDrawingEffect(NULL, *(DWRITE_TEXT_RANGE *)&textRange));
		}
		else
		{
			ComUtils::CheckResult(GetNative()->SetDrawingEffect(drawingEffect->GetNative(), *(DWRITE_TEXT_RANGE *)&textRange));
		}
	}

	Managed::Graphics::DirectWrite::FontCollection^ TextLayout::GetFontCollection(Int32 position)
	{
		IDWriteFontCollection* fontCollection;
		ComUtils::CheckResult(GetNative()->GetFontCollection(position, &fontCollection, NULL));
		return gcnew Managed::Graphics::DirectWrite::FontCollection(fontCollection);
	}

	Managed::Graphics::DirectWrite::FontCollection^ TextLayout::GetFontCollection(Int32 position, [Out]TextRange% textRange)
	{
		IDWriteFontCollection* fontCollection;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetFontCollection(position, &fontCollection, (DWRITE_TEXT_RANGE *)pTextRange));
		return gcnew Managed::Graphics::DirectWrite::FontCollection(fontCollection);
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
		return (Managed::Graphics::DirectWrite::FontStretch)value;
	}

	FontStretch TextLayout::GetFontStretch(Int32 position, [Out]TextRange% textRange)
	{
		DWRITE_FONT_STRETCH value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetFontStretch(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return (Managed::Graphics::DirectWrite::FontStretch)value;
	}

	FontStyle TextLayout::GetFontStyle(Int32 position)
	{
		DWRITE_FONT_STYLE value;
		ComUtils::CheckResult(GetNative()->GetFontStyle(position, &value, NULL));
		return (Managed::Graphics::DirectWrite::FontStyle)value;
	}

	FontStyle TextLayout::GetFontStyle(Int32 position, [Out]TextRange% textRange)
	{
		DWRITE_FONT_STYLE value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetFontStyle(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return (Managed::Graphics::DirectWrite::FontStyle)value;
	}

	FontWeight TextLayout::GetFontWeight(Int32 position)
	{
		DWRITE_FONT_WEIGHT value;
		ComUtils::CheckResult(GetNative()->GetFontWeight(position, &value, NULL));
		return (Managed::Graphics::DirectWrite::FontWeight)value;
	}

	FontWeight TextLayout::GetFontWeight(Int32 position, [Out]TextRange% textRange)
	{
		DWRITE_FONT_WEIGHT value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetFontWeight(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		return (Managed::Graphics::DirectWrite::FontWeight)value;
	}

	array<Managed::Graphics::DirectWrite::LineMetrics>^ TextLayout::LineMetrics::get()
	{
		UINT32 count;
		HRESULT hr = GetNative()->GetLineMetrics(NULL, 0, &count);
		if(FAILED(hr) && hr != E_NOT_SUFFICIENT_BUFFER)
			Marshal::ThrowExceptionForHR(hr);
		array<Managed::Graphics::DirectWrite::LineMetrics>^ metrics = gcnew array<Managed::Graphics::DirectWrite::LineMetrics>(count);
		pin_ptr<Managed::Graphics::DirectWrite::LineMetrics> pMetrics = &metrics[0];
		ComUtils::CheckResult(GetNative()->GetLineMetrics((DWRITE_LINE_METRICS *)pMetrics, count, &count));
		return metrics;
	}

	InlineObject^ TextLayout::GetInlineObject(Int32 position)
	{
		IDWriteInlineObject * value;
		ComUtils::CheckResult(GetNative()->GetInlineObject(position, &value, NULL));
		InlineObjectNative* inlineObjectNative;
		if(SUCCEEDED(value->QueryInterface(__uuidof(InlineObjectNative), (void**)&inlineObjectNative)))
		{
			return inlineObjectNative->GetObject();
		}
		return gcnew InlineObjectWrapper(value, false);
	}

	InlineObject^ TextLayout::GetInlineObject(Int32 position, [Out]TextRange% textRange)
	{
		IDWriteInlineObject * value;
		pin_ptr<TextRange> pTextRange = &textRange;
		ComUtils::CheckResult(GetNative()->GetInlineObject(position, &value, (DWRITE_TEXT_RANGE *)pTextRange));
		InlineObjectNative* inlineObjectNative;
		if(SUCCEEDED(value->QueryInterface(__uuidof(InlineObjectNative), (void**)&inlineObjectNative)))
		{
			return inlineObjectNative->GetObject();
		}
		return gcnew InlineObjectWrapper(value, false);
	}

	HitTestMetrics TextLayout::HitTestPoint(Single x, Single y, [Out]Boolean% isTrailingHit, [Out]Boolean% isInside)
	{
		HitTestMetrics metrics;
		BOOL b1, b2;
		ComUtils::CheckResult(GetNative()->HitTestPoint(x, y, &b1, &b2, (DWRITE_HIT_TEST_METRICS*)&metrics));
		isTrailingHit = b1 != 0;
		isInside = b2 != 0;
		return metrics;
	}

	HitTestMetrics TextLayout::HitTestTextPosition(Int32 textPosition, Boolean isTrailingHit, [Out]Single% pointX, [Out]Single% pointY)
	{
		HitTestMetrics metrics;
		FLOAT x, y;
		ComUtils::CheckResult(
			GetNative()->HitTestTextPosition(
				textPosition, 
				isTrailingHit, 
				&x, 
				&y, 
				(DWRITE_HIT_TEST_METRICS*)&metrics));
		pointX = x;
		pointY = y;
		return metrics;
	}

	array<HitTestMetrics>^ TextLayout::HitTestTextRange(Int32 textPosition, Int32 textLength, Single originX, Single originY)
	{
		UINT32 count;
		HRESULT hr = GetNative()->HitTestTextRange(textPosition, textLength, originX, originY, NULL, 0, &count);
		if(hr != E_NOT_SUFFICIENT_BUFFER)
			ComUtils::CheckResult(hr);
		
		array<HitTestMetrics>^ metrics = gcnew array<HitTestMetrics>(count);
		pin_ptr<HitTestMetrics> pMetrics = &metrics[0];
		
		ComUtils::CheckResult(
			GetNative()->HitTestTextRange(
				textPosition, 
				textLength, 
				originX, 
				originY, 
				(DWRITE_HIT_TEST_METRICS *)pMetrics, 
				count, 
				&count));
		
		return metrics;
	}

	System::Globalization::CultureInfo^ TextLayout::GetCulture(Int32 position)
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

	System::Globalization::CultureInfo^ TextLayout::GetCulture(Int32 position, [Out]TextRange% textRange)
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

	void TextLayout::SetFontCollection(Managed::Graphics::DirectWrite::FontCollection^ fontCollection, TextRange textRange)
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

	void TextLayout::SetFontStretch(Managed::Graphics::DirectWrite::FontStretch fontStretch, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetFontStretch((DWRITE_FONT_STRETCH)fontStretch, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetFontStyle(Managed::Graphics::DirectWrite::FontStyle fontStyle, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetFontStyle((DWRITE_FONT_STYLE)fontStyle, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetFontWeight(Managed::Graphics::DirectWrite::FontWeight fontWeight, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetFontWeight((DWRITE_FONT_WEIGHT)fontWeight, *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetInlineObject(InlineObject^ inlineObject, TextRange textRange)
	{
		ComUtils::CheckResult(GetNative()->SetInlineObject(inlineObject->GetNative(), *(DWRITE_TEXT_RANGE *)&textRange));
	}

	void TextLayout::SetCulture(System::Globalization::CultureInfo^ cultureInfo, TextRange textRange)
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