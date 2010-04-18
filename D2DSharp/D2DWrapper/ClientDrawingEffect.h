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

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	class ClientDrawingEffectNative;

	public ref class ClientDrawingEffect abstract
	{
	protected:
		ClientDrawingEffect();
	public:
		~ClientDrawingEffect()
		{
			this->!ClientDrawingEffect();
		}
		!ClientDrawingEffect();
	internal:
		IUnknown* GetNative();
	private:
		ClientDrawingEffectNative* _native;
	};

	class __declspec(uuid("F9F4394C-ADCE-4644-B619-C4F89787E216")) 
		ClientDrawingEffectNative: public IUnknown
	{
	public:
		ClientDrawingEffectNative(ClientDrawingEffect^ managed): _managed(managed), _refCount(1)
		{
		}
	public:
		ClientDrawingEffect^ GetObject()
		{
			return _managed;
		}
        unsigned long STDMETHODCALLTYPE AddRef();
        unsigned long STDMETHODCALLTYPE Release();
        HRESULT STDMETHODCALLTYPE QueryInterface(
            IID const& riid,
            void** ppvObject
        );

		gcroot<ClientDrawingEffect^> _managed;
		LONG _refCount;
	};
}}}