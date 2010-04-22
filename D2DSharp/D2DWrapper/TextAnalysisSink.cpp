/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;

TextAnalysisSink::TextAnalysisSink()
{
	_native = new TextAnalysisSinkNative(this);
}

TextAnalysisSink::~TextAnalysisSink()
{
	this->!TextAnalysisSink();
}

TextAnalysisSink::!TextAnalysisSink()
{
	if(_native != NULL)
	{
		_native->Release();
		_native = NULL;
	}
}

HRESULT STDMETHODCALLTYPE TextAnalysisSinkNative::SetScriptAnalysis(
	UINT32 textPosition,
	UINT32 textLength,
	__in DWRITE_SCRIPT_ANALYSIS const* scriptAnalysis
	)
{
	try
	{
		_managed->SetScriptAnalysis(textPosition, textLength, *(ScriptAnalysis*)scriptAnalysis);
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TextAnalysisSinkNative::SetLineBreakpoints(
	UINT32 textPosition,
	UINT32 textLength,
	__in_ecount(textLength) DWRITE_LINE_BREAKPOINT const* lineBreakpoints
	)
{
	try
	{
		_managed->SetLineBreakpoints(textPosition, textLength, *(LineBreakpoint*)lineBreakpoints);
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TextAnalysisSinkNative::SetBidiLevel(
	UINT32 textPosition,
	UINT32 textLength,
	UINT8 explicitLevel,
	UINT8 resolvedLevel
	)
{
	try
	{
		_managed->SetBidiLevel(textPosition, textLength, explicitLevel, resolvedLevel);
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TextAnalysisSinkNative::SetNumberSubstitution(
	UINT32 textPosition,
	UINT32 textLength,
	__notnull IDWriteNumberSubstitution* numberSubstitution
	)
{
	try
	{
		NumberSubstitution^ numberSubstitutionManaged = gcnew NumberSubstitution(numberSubstitution);
		_managed->SetNumberSubstitution(textPosition, textLength, numberSubstitutionManaged);
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

unsigned long STDMETHODCALLTYPE TextAnalysisSinkNative::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

unsigned long STDMETHODCALLTYPE TextAnalysisSinkNative::Release()
{
    if (InterlockedDecrement(&_refCount) == 0)
    {
        delete this;
        return 0;
    }
    return _refCount;
}

HRESULT STDMETHODCALLTYPE TextAnalysisSinkNative::QueryInterface(IID const& riid, void** ppvObject)
{
	if(__uuidof(IDWriteTextAnalysisSink) == riid)
	{
		*ppvObject = static_cast<IDWriteTextAnalysisSink*>(this);
	}
	else if (__uuidof(IUnknown) == riid)
    {
        *ppvObject = static_cast<IUnknown*>(this);
    }
    else
    {
        *ppvObject = NULL;
        return E_FAIL;
    }
    return S_OK;
}
