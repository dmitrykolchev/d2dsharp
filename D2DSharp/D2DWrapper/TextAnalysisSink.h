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
	ref class NumberSubstitution;
	class TextAnalysisSinkNative;

	public ref class TextAnalysisSink abstract
	{
	protected:
		TextAnalysisSink();
	public:
		~TextAnalysisSink();
		!TextAnalysisSink();
	public:
		virtual void SetBidiLevel(UInt32 textPosition, UInt32 textLength, Byte explicitLevel, Byte resolvedLevel) = 0;
		virtual void SetLineBreakpoints(UInt32 textPosition, UInt32 textLength, LineBreakpoint lineBreakPoints) = 0;
		virtual void SetNumberSubstitution(UInt32 textPosition, UInt32 textLength, NumberSubstitution^ numberSubstitution) = 0;
		virtual void SetScriptAnalysis(UInt32 textPosition, UInt32 textLength, ScriptAnalysis scriptAnalysis) = 0;
	internal:
		IDWriteTextAnalysisSink* GetNative()
		{
			return _native;
		}
	private:
		IDWriteTextAnalysisSink* _native;
	};

	class TextAnalysisSinkNative: public IDWriteTextAnalysisSink
	{
	public:
		TextAnalysisSinkNative(TextAnalysisSink^ managed):
			_managed(managed),
			_refCount(1)
		{
		}
	protected:
		~TextAnalysisSinkNative()
		{
			_managed = nullptr;
			delete this;
		}
	public:
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
	private:
		gcroot<TextAnalysisSink^> _managed;
		ULONG _refCount;
	};
}}}