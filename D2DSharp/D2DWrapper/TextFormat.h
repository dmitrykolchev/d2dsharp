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
				return (Managed::Graphics::DirectWrite::FlowDirection)GetNative()->GetFlowDirection(); 
			}
			void set(Managed::Graphics::DirectWrite::FlowDirection value) 
			{ 
				GetNative()->SetFlowDirection((DWRITE_FLOW_DIRECTION) value); 
			}
		}

		property FLOAT IncrementalTabStop
		{
			FLOAT get() { return GetNative()->GetIncrementalTabStop(); }
			void set(FLOAT value) { GetNative()->SetIncrementalTabStop(value); }
		}

		property Managed::Graphics::DirectWrite::ParagraphAlignment ParagraphAlignment
		{
			Managed::Graphics::DirectWrite::ParagraphAlignment get() 
			{ 
				return (Managed::Graphics::DirectWrite::ParagraphAlignment)GetNative()->GetParagraphAlignment(); 
			}
			void set(Managed::Graphics::DirectWrite::ParagraphAlignment value) 
			{ 
				GetNative()->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT) value); 
			}
		}

		property Managed::Graphics::DirectWrite::ReadingDirection ReadingDirection
		{
			Managed::Graphics::DirectWrite::ReadingDirection get() 
			{ 
				return (Managed::Graphics::DirectWrite::ReadingDirection)GetNative()->GetReadingDirection(); 
			}
			void set(Managed::Graphics::DirectWrite::ReadingDirection value) 
			{ 
				GetNative()->SetReadingDirection((DWRITE_READING_DIRECTION) value); 
			}
		}

		property Managed::Graphics::DirectWrite::TextAlignment TextAlignment
		{
			Managed::Graphics::DirectWrite::TextAlignment get() 
			{ 
				return (Managed::Graphics::DirectWrite::TextAlignment)GetNative()->GetTextAlignment(); 
			}
			void set(Managed::Graphics::DirectWrite::TextAlignment value) 
			{ 
				GetNative()->SetTextAlignment((DWRITE_TEXT_ALIGNMENT) value); 
			}
		}

	internal:
		IDWriteTextFormat* GetNative() new
		{
			return (IDWriteTextFormat*)ComWrapper::GetNative();
		}
	};
}}}