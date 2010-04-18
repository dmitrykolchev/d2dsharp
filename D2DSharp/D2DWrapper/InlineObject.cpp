/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;

InlineObject::InlineObject()
{
	_native = new InlineObjectNative(this);
}

InlineObject::InlineObject(IDWriteInlineObject* native, bool addRef)
{
	_native = native;
	if(addRef)
		_native->AddRef();
}

InlineObject::!InlineObject()
{
	if(_native)
	{
		_native->Release();
		_native = NULL;
	}
}

IDWriteInlineObject* InlineObject::GetNative()
{
	return static_cast<IDWriteInlineObject*>(_native);
}

//
// InlineObjectWrapper
//
void InlineObjectWrapper::Draw(
	ITextRenderer^ renderer, 
	Single originX, 
	Single originY, 
	Boolean isSideways, 
	Boolean isRtl, 
	ClientDrawingEffect^ clientDrawingEffect)
{
	//TODO: redesign ITextRenderer
	throw gcnew NotImplementedException();
}

InlineObjectMetrics InlineObjectWrapper::Metrics::get()
{
	InlineObjectMetrics metrics;
	ComUtils::CheckResult(GetNative()->GetMetrics((DWRITE_INLINE_OBJECT_METRICS*)&metrics));
	return metrics;
}

Managed::Graphics::DirectWrite::OverhangMetrics InlineObjectWrapper::OverhangMetrics::get()
{
	Managed::Graphics::DirectWrite::OverhangMetrics metrics;
	ComUtils::CheckResult(GetNative()->GetOverhangMetrics((DWRITE_OVERHANG_METRICS*)&metrics));
	return metrics;
}

BreakCondition InlineObjectWrapper::BreakConditionBefore::get()
{
	DWRITE_BREAK_CONDITION before;
	DWRITE_BREAK_CONDITION after;
	ComUtils::CheckResult(GetNative()->GetBreakConditions(&before, &after));
	return (BreakCondition)before;
}

BreakCondition InlineObjectWrapper::BreakConditionAfter::get()
{
	DWRITE_BREAK_CONDITION before;
	DWRITE_BREAK_CONDITION after;
	ComUtils::CheckResult(GetNative()->GetBreakConditions(&before, &after));
	return (BreakCondition)after;
}

//
// InlineObjectNative
//
HRESULT STDMETHODCALLTYPE InlineObjectNative::Draw(
	__maybenull void* clientDrawingContext,
	IDWriteTextRenderer* renderer,
	FLOAT originX,
	FLOAT originY,
	BOOL isSideways,
	BOOL isRightToLeft,
	__maybenull IUnknown* clientDrawingEffect
	)
{
	try
	{
		ClientDrawingEffect^ clientDrawingEffectManaged = nullptr;
		if(clientDrawingEffect)
		{
			ClientDrawingEffectNative* native = NULL;
			if(SUCCEEDED(clientDrawingEffect->QueryInterface(__uuidof(ClientDrawingEffectNative), (void**)&native)))
			{
				clientDrawingEffectManaged = native->GetObject();
			}
		}
		GetObject()->Draw(nullptr, originX, originY, isSideways != 0, isRightToLeft != 0, clientDrawingEffectManaged);
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE InlineObjectNative::GetMetrics(__out DWRITE_INLINE_OBJECT_METRICS* metrics)
{
	try
	{
		InlineObjectMetrics value = GetObject()->Metrics;
		*metrics = *(DWRITE_INLINE_OBJECT_METRICS *)&value;
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE InlineObjectNative::GetOverhangMetrics(__out DWRITE_OVERHANG_METRICS* overhangs)
{
	try
	{
		OverhangMetrics metrics = GetObject()->OverhangMetrics;
		*overhangs = *(DWRITE_OVERHANG_METRICS*)&metrics;
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE InlineObjectNative::GetBreakConditions(
	__out DWRITE_BREAK_CONDITION* breakConditionBefore,
	__out DWRITE_BREAK_CONDITION* breakConditionAfter
	)
{
	try
	{
		InlineObject^ inlineObject = GetObject();
		*breakConditionBefore = (DWRITE_BREAK_CONDITION)inlineObject->BreakConditionBefore;
		*breakConditionAfter = (DWRITE_BREAK_CONDITION)inlineObject->BreakConditionAfter;
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

unsigned long STDMETHODCALLTYPE InlineObjectNative::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

unsigned long STDMETHODCALLTYPE InlineObjectNative::Release()
{
    if (InterlockedDecrement(&_refCount) == 0)
    {
        delete this;
        return 0;
    }
    return _refCount;
}

HRESULT STDMETHODCALLTYPE InlineObjectNative::QueryInterface(IID const& riid, void** ppvObject)
{
	if(__uuidof(InlineObjectNative) == riid)
	{
		*ppvObject = static_cast<InlineObjectNative*>(this);
	}
	else if(__uuidof(IDWriteInlineObject) == riid)
	{
		*ppvObject = static_cast<IDWriteInlineObject*>(this);
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
