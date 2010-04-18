/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

using namespace Managed::Graphics::DirectWrite;

ClientDrawingEffect::ClientDrawingEffect()
{
	_native = new ClientDrawingEffectNative(this);
}

ClientDrawingEffect::!ClientDrawingEffect()
{
	if(_native != NULL)
	{
		_native->Release();
		_native = NULL;
	}
}

IUnknown* ClientDrawingEffect::GetNative()
{
	return static_cast<IUnknown*>(_native);
}

unsigned long STDMETHODCALLTYPE ClientDrawingEffectNative::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

unsigned long STDMETHODCALLTYPE ClientDrawingEffectNative::Release()
{
    if (InterlockedDecrement(&_refCount) == 0)
    {
        delete this;
        return 0;
    }
    return _refCount;
}

HRESULT STDMETHODCALLTYPE ClientDrawingEffectNative::QueryInterface(IID const& riid, void** ppvObject)
{
	if(__uuidof(ClientDrawingEffectNative) == riid)
	{
		*ppvObject = static_cast<ClientDrawingEffectNative*>(this);
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


