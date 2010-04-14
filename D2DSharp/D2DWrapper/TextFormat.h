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
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DykBits::Runtime::InteropServices;

namespace DykBits { namespace Graphics { namespace DirectWrite
{
	/// <summary>
	/// Direction for how lines of text are placed relative to one another.
	/// </summary>
	public enum class FlowDirection
	{
	    /// <summary>
	    /// Text lines are placed from top to bottom.
	    /// </summary>
	    TopToBottom = DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM
	};


	public ref class TextFormat: ComWrapper
	{
	internal:
		TextFormat(IDWriteTextFormat* native): ComWrapper(native)
		{
		}
	public:
		property DykBits::Graphics::DirectWrite::FlowDirection FlowDirection
		{
			DykBits::Graphics::DirectWrite::FlowDirection get() 
			{ 
				return (DykBits::Graphics::DirectWrite::FlowDirection)GetNative()->GetFlowDirection(); 
			}
			void set(DykBits::Graphics::DirectWrite::FlowDirection value) 
			{ 
				GetNative()->SetFlowDirection((DWRITE_FLOW_DIRECTION) value); 
			}
		}

		property FLOAT IncrementalTabStop
		{
			FLOAT get() { return GetNative()->GetIncrementalTabStop(); }
			void set(FLOAT value) { GetNative()->SetIncrementalTabStop(value); }
		}

		property DykBits::Graphics::DirectWrite::ParagraphAlignment ParagraphAlignment
		{
			DykBits::Graphics::DirectWrite::ParagraphAlignment get() 
			{ 
				return (DykBits::Graphics::DirectWrite::ParagraphAlignment)GetNative()->GetParagraphAlignment(); 
			}
			void set(DykBits::Graphics::DirectWrite::ParagraphAlignment value) 
			{ 
				GetNative()->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT) value); 
			}
		}

		property DykBits::Graphics::DirectWrite::ReadingDirection ReadingDirection
		{
			DykBits::Graphics::DirectWrite::ReadingDirection get() 
			{ 
				return (DykBits::Graphics::DirectWrite::ReadingDirection)GetNative()->GetReadingDirection(); 
			}
			void set(DykBits::Graphics::DirectWrite::ReadingDirection value) 
			{ 
				GetNative()->SetReadingDirection((DWRITE_READING_DIRECTION) value); 
			}
		}

		property DykBits::Graphics::DirectWrite::TextAlignment TextAlignment
		{
			DykBits::Graphics::DirectWrite::TextAlignment get() 
			{ 
				return (DykBits::Graphics::DirectWrite::TextAlignment)GetNative()->GetTextAlignment(); 
			}
			void set(DykBits::Graphics::DirectWrite::TextAlignment value) 
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