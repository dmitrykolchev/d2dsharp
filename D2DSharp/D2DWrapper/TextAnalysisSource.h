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
	public ref class TextAnalysisSource abstract
	{
	protected:
		TextAnalysisSource(String^ text);
	public:
		~TextAnalysisSource();
		!TextAnalysisSource();
	public:
		virtual System::Globalization::CultureInfo^ GetCulture(UInt32 testPosition, [Out]UInt32% textLength) = 0;

		virtual NumberSubstitution^ GetNumberSubstitution(UInt32 testPosition, [Out]UInt32% textLength) = 0;

		virtual property Managed::Graphics::DirectWrite::ReadingDirection ReadingDirection 
		{
			Managed::Graphics::DirectWrite::ReadingDirection get()
			{
				return Managed::Graphics::DirectWrite::ReadingDirection::LeftToRight;
			}
		}
		property String^ Text
		{
			String^ get() { return _text; }
		}
	internal:
		IDWriteTextAnalysisSource* GetNative()
		{
			return _native;
		}
	private:
		String^ _text;
		IDWriteTextAnalysisSource* _native;
	};


	class TextAnalysisSourceNative: public IDWriteTextAnalysisSource
	{
	public:
		TextAnalysisSourceNative(TextAnalysisSource^ managed, String^ text):
			_refCount(1),
			_managed(managed),
			_localeName(NULL)
		{
			_text = (wchar_t*)Marshal::StringToHGlobalUni(text).ToPointer();
			_length = text->Length;
		}
	public:
		STDMETHOD(GetTextAtPosition)(
			UINT32 textPosition,
			__out WCHAR const** textString,
			__out UINT32* textLength
			);

		STDMETHOD(GetTextBeforePosition)(
			UINT32 textPosition,
			__out WCHAR const** textString,
			__out UINT32* textLength
			);

	    STDMETHOD_(DWRITE_READING_DIRECTION, GetParagraphReadingDirection)();

		STDMETHOD(GetLocaleName)(
			UINT32 textPosition,
			__out UINT32* textLength,
			__out_z WCHAR const** localeName
			);

		STDMETHOD(GetNumberSubstitution)(
			UINT32 textPosition,
			__out UINT32* textLength,
			__out IDWriteNumberSubstitution** numberSubstitution
			);
		unsigned long STDMETHODCALLTYPE AddRef();
        unsigned long STDMETHODCALLTYPE Release();
        HRESULT STDMETHODCALLTYPE QueryInterface(IID const& riid, void** ppvObject);
	protected:
		~TextAnalysisSourceNative()
		{
			_managed = nullptr;
			if(_localeName)
				LocalFree(_localeName);
			if(_text)
				LocalFree(_text);
		}
	private:
		ULONG _refCount;
		gcroot<TextAnalysisSource^> _managed;
		wchar_t *_localeName;
		wchar_t *_text;
		UINT32 _length;
	};
}}}