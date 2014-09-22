/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace DirectWrite
{

	ref class FontCollection;

	public ref class TextFormat: ComWrapper
	{
	internal:
		TextFormat(IDWriteTextFormat* native): ComWrapper(native)
		{
		}
	public:
		property Managed::Graphics::DirectWrite::FlowDirection FlowDirection
		{
			Managed::Graphics::DirectWrite::FlowDirection get() 
			{ 
				return (Managed::Graphics::DirectWrite::FlowDirection)GetNative<IDWriteTextFormat>()->GetFlowDirection();
			}
			void set(Managed::Graphics::DirectWrite::FlowDirection value) 
			{ 
				GetNative<IDWriteTextFormat>()->SetFlowDirection((DWRITE_FLOW_DIRECTION) value);
			}
		}

		property FLOAT IncrementalTabStop
		{
			FLOAT get() { return GetNative<IDWriteTextFormat>()->GetIncrementalTabStop(); }
			void set(FLOAT value) { GetNative<IDWriteTextFormat>()->SetIncrementalTabStop(value); }
		}

		property Managed::Graphics::DirectWrite::ParagraphAlignment ParagraphAlignment
		{
			Managed::Graphics::DirectWrite::ParagraphAlignment get() 
			{ 
				return (Managed::Graphics::DirectWrite::ParagraphAlignment)GetNative<IDWriteTextFormat>()->GetParagraphAlignment();
			}
			void set(Managed::Graphics::DirectWrite::ParagraphAlignment value) 
			{ 
				GetNative<IDWriteTextFormat>()->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT) value);
			}
		}

		property Managed::Graphics::DirectWrite::ReadingDirection ReadingDirection
		{
			Managed::Graphics::DirectWrite::ReadingDirection get() 
			{ 
				return (Managed::Graphics::DirectWrite::ReadingDirection)GetNative<IDWriteTextFormat>()->GetReadingDirection();
			}
			void set(Managed::Graphics::DirectWrite::ReadingDirection value) 
			{ 
				GetNative<IDWriteTextFormat>()->SetReadingDirection((DWRITE_READING_DIRECTION) value);
			}
		}

		property Managed::Graphics::DirectWrite::TextAlignment TextAlignment
		{
			Managed::Graphics::DirectWrite::TextAlignment get() 
			{ 
				return (Managed::Graphics::DirectWrite::TextAlignment)GetNative<IDWriteTextFormat>()->GetTextAlignment();
			}
			void set(Managed::Graphics::DirectWrite::TextAlignment value) 
			{ 
				GetNative<IDWriteTextFormat>()->SetTextAlignment((DWRITE_TEXT_ALIGNMENT) value);
			}
		}

		property Managed::Graphics::DirectWrite::FontCollection^ FontCollection
		{
			Managed::Graphics::DirectWrite::FontCollection^ get();
		}

		property String^ FontFamilyName
		{
			String^ get();
		}

		property Single FontSize
		{
			Single get();
		}

		property Managed::Graphics::DirectWrite::FontStretch FontStretch
		{
			Managed::Graphics::DirectWrite::FontStretch get();
		}

		property Managed::Graphics::DirectWrite::FontStyle FontStyle
		{
			Managed::Graphics::DirectWrite::FontStyle get();
		}

		property Managed::Graphics::DirectWrite::FontWeight FontWeight
		{
			Managed::Graphics::DirectWrite::FontWeight get();
		}

		property Managed::Graphics::DirectWrite::LineSpacing LineSpacing
		{
			Managed::Graphics::DirectWrite::LineSpacing get();
			void set(Managed::Graphics::DirectWrite::LineSpacing value);
		}

		property System::Globalization::CultureInfo^ Culture
		{
			System::Globalization::CultureInfo^ get();
		}

		property Managed::Graphics::DirectWrite::Trimming Trimming
		{
			Managed::Graphics::DirectWrite::Trimming get();
			void set(Managed::Graphics::DirectWrite::Trimming value);
		}

		property Managed::Graphics::DirectWrite::WordWrapping WordWrapping
		{
			Managed::Graphics::DirectWrite::WordWrapping get();
			void set(Managed::Graphics::DirectWrite::WordWrapping value);
		}
	};
}}}