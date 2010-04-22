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
	protected:
		
		virtual void OnSetBidiLevel(UInt32 textPosition, UInt32 textLength, Byte explicitLevel, Byte resolvedLevel)
		{
			if(SetBidiLevelCallback != nullptr)
				SetBidiLevelCallback(textPosition, textLength, explicitLevel, resolvedLevel);
		}
		
		virtual void OnSetLineBreakpoints(UInt32 textPosition, UInt32 textLength, LineBreakpoint lineBreakPoints)
		{
			if(SetLineBreakpointsCallback != nullptr)
			{
				SetLineBreakpointsCallback(textPosition, textLength, lineBreakPoints);
			}
		}

		virtual void OnSetNumberSubstitution(UInt32 textPosition, UInt32 textLength, NumberSubstitution^ numberSubstitution)
		{
			if(SetNumberSubstitutionCallback != nullptr)
			{
				SetNumberSubstitutionCallback(textPosition, textLength, numberSubstitution);
			}
		}

		virtual void OnSetScriptAnalysis(UInt32 textPosition, UInt32 textLength, ScriptAnalysis scriptAnalysis)
		{
			if(SetScriptAnalysisCallback != nullptr)
			{
				SetScriptAnalysisCallback(textPosition, textLength, scriptAnalysis);
			}
		}
	internal:
		void SetBidiLevel(UInt32 textPosition, UInt32 textLength, Byte explicitLevel, Byte resolvedLevel)
		{
			OnSetBidiLevel(textPosition, textLength, explicitLevel, resolvedLevel);
		}
		void SetLineBreakpoints(UInt32 textPosition, UInt32 textLength, LineBreakpoint lineBreakPoints)
		{
			OnSetLineBreakpoints(textPosition, textLength, lineBreakPoints);
		}
		void SetNumberSubstitution(UInt32 textPosition, UInt32 textLength, NumberSubstitution^ numberSubstitution)
		{
			OnSetNumberSubstitution(textPosition, textLength, numberSubstitution);
		}
		void SetScriptAnalysis(UInt32 textPosition, UInt32 textLength, ScriptAnalysis scriptAnalysis)
		{
			OnSetScriptAnalysis(textPosition, textLength, scriptAnalysis);
		}
	internal:
		IDWriteTextAnalysisSource* GetNative()
		{
			return _native;
		}
	private:
		String^ _text;
		IDWriteTextAnalysisSource* _native;
	public:
		Action<UInt32, UInt32, Byte, Byte>^ SetBidiLevelCallback;
		Action<UInt32, UInt32, LineBreakpoint>^ SetLineBreakpointsCallback;
		Action<UInt32, UInt32, NumberSubstitution^>^ SetNumberSubstitutionCallback;
		Action<UInt32, UInt32, ScriptAnalysis>^ SetScriptAnalysisCallback;
	};


	class TextAnalysisSourceNative: 
		public IDWriteTextAnalysisSource,
		public IDWriteTextAnalysisSink
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
		//
		// IDWriteTextAnalysisSource
		//
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
		//
		// IDWriteTextAnalysisSink
		//
		STDMETHOD(SetScriptAnalysis)(
			UINT32 textPosition,
			UINT32 textLength,
			__in DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis
			);

		STDMETHOD(SetLineBreakpoints)(
			UINT32 textPosition,
			UINT32 textLength,
			__in_ecount(textLength) DWRITE_LINE_BREAKPOINT const* lineBreakpoints
			);

		STDMETHOD(SetBidiLevel)(
			UINT32 textPosition,
			UINT32 textLength,
			UINT8 explicitLevel,
			UINT8 resolvedLevel
			);

		STDMETHOD(SetNumberSubstitution)(
			UINT32 textPosition,
			UINT32 textLength,
			__notnull IDWriteNumberSubstitution* numberSubstitution
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