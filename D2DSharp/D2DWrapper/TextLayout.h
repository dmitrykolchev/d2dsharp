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
	interface class ITextRenderer;
	ref class ClientDrawingEffect;
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
		property array<Managed::Graphics::DirectWrite::ClusterMetrics>^ ClusterMetrics
		{
			array<Managed::Graphics::DirectWrite::ClusterMetrics>^ get();
		}
		property Single MinWidth
		{
			Single get()
			{
				FLOAT minWidth;
				ComUtils::CheckResult(GetNative<IDWriteTextLayout>()->DetermineMinWidth(&minWidth));
				return minWidth;
			}
		}

		property Single MaxHeight
		{
			Single get()
			{
				return GetNative<IDWriteTextLayout>()->GetMaxHeight();
			}
			void set(Single value)
			{
				ComUtils::CheckResult(GetNative<IDWriteTextLayout>()->SetMaxHeight(value));
			}
		}

		property Single MaxWidth
		{
			Single get()
			{
				return GetNative<IDWriteTextLayout>()->GetMaxWidth();
			}
			void set(Single value)
			{
				ComUtils::CheckResult(GetNative<IDWriteTextLayout>()->SetMaxWidth(value));
			}
		}

		ClientDrawingEffect^ GetDrawingEffect(Int32 position);
		ClientDrawingEffect^ GetDrawingEffect(Int32 position, [Out]TextRange% textRange);

		Managed::Graphics::DirectWrite::FontCollection^ GetFontCollection(Int32 position);
		Managed::Graphics::DirectWrite::FontCollection^ GetFontCollection(Int32 position, [Out]TextRange% textRange);
		
		String^ GetFontFamilyName(Int32 position);
		String^ GetFontFamilyName(Int32 position, [Out]TextRange% textRange);
		
		Single GetFontSize(Int32 position);
		Single GetFontSize(Int32 position, [Out]TextRange% textRange);
		
		Managed::Graphics::DirectWrite::FontStretch GetFontStretch(Int32 position);
		Managed::Graphics::DirectWrite::FontStretch GetFontStretch(Int32 position, [Out]TextRange% textRange);
		
		Managed::Graphics::DirectWrite::FontStyle GetFontStyle(Int32 position);
		Managed::Graphics::DirectWrite::FontStyle GetFontStyle(Int32 position, [Out]TextRange% textRange);
		
		Managed::Graphics::DirectWrite::FontWeight GetFontWeight(Int32 position);
		Managed::Graphics::DirectWrite::FontWeight GetFontWeight(Int32 position, [Out]TextRange% textRange);
		
		InlineObject^ GetInlineObject(Int32 position);
		InlineObject^ GetInlineObject(Int32 position, [Out]TextRange% textRange);
		
		property array<Managed::Graphics::DirectWrite::LineMetrics>^ LineMetrics
		{
			array<Managed::Graphics::DirectWrite::LineMetrics>^ get();
		}
		
		System::Globalization::CultureInfo^ TextLayout::GetCulture(Int32 position);
		System::Globalization::CultureInfo^ TextLayout::GetCulture(Int32 position, [Out]TextRange% textRange);
		
		property TextMetrics Metrics
		{
			TextMetrics get()
			{
				TextMetrics value;
				ComUtils::CheckResult(GetNative<IDWriteTextLayout>()->GetMetrics((DWRITE_TEXT_METRICS*) &value));
				return value;
			}
		}
		property Managed::Graphics::DirectWrite::OverhangMetrics OverhangMetrics
		{
			Managed::Graphics::DirectWrite::OverhangMetrics get()
			{
				Managed::Graphics::DirectWrite::OverhangMetrics value;
				ComUtils::CheckResult(GetNative<IDWriteTextLayout>()->GetOverhangMetrics((DWRITE_OVERHANG_METRICS *) &value));
				return value;
			}
		}
		
		Boolean GetStrikethrough(Int32 position);
		Boolean GetStrikethrough(Int32 position, [Out]TextRange% textRange);
		
		Typography^ GetTypography(Int32 position);
		Typography^ GetTypography(Int32 position, [Out]TextRange% textRange);
		
		Boolean GetUnderline(Int32 position);
		Boolean GetUnderline(Int32 position, [Out]TextRange% textRange);
		
		HitTestMetrics HitTestPoint(Single x, Single y, [Out]Boolean% isTrailingHit, [Out]Boolean% isInside);
		HitTestMetrics HitTestTextPosition(Int32 textPosition, Boolean isTrailingHit, [Out]Single% pointX, [Out]Single% pointY);
		array<HitTestMetrics>^ HitTestTextRange(Int32 textPosition, Int32 textLength, Single originX, Single originY);
		
		void SetDrawingEffect(ClientDrawingEffect^ drawingEffect, TextRange textRange);
		
		void SetFontCollection(Managed::Graphics::DirectWrite::FontCollection^ fontCollection, TextRange textRange);
		
		void SetFontFamilyName(String^ fontFamilyName, TextRange textRange);
		
		void SetFontSize(Single fontSize, TextRange textRange);
		
		void SetFontStretch(Managed::Graphics::DirectWrite::FontStretch fontStretch, TextRange textRange);
		
		void SetFontStyle(Managed::Graphics::DirectWrite::FontStyle fontStyle, TextRange textRange);
		
		void SetFontWeight(Managed::Graphics::DirectWrite::FontWeight fontWeight, TextRange textRange);
		
		void SetInlineObject(InlineObject^ inlineObject, TextRange textRange);
		
		void SetCulture(System::Globalization::CultureInfo^ cultureInfo, TextRange textRange);
		
		void SetStrikethrough(Boolean hasStrikethrough, TextRange textRange);
		
		void SetTypography(Typography^ typography, TextRange textRange);
		
		void SetUnderline(Boolean hasUnderline, TextRange textRange);
	};
}}}