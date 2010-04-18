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
	class InlineObjectNative;
	interface class ITextRenderer;
	ref class ClientDrawingEffect;

	public ref class InlineObject abstract
	{
	protected:
		InlineObject();
	internal:
		InlineObject(IDWriteInlineObject* native, bool addRef);
	public:
		~InlineObject()
		{
			this->!InlineObject();
		}
		!InlineObject();
	public:
		virtual void Draw(
			ITextRenderer^ renderer, 
			Single originX, 
			Single originY, 
			Boolean isSideways, 
			Boolean isRtl, 
			ClientDrawingEffect^ clientDrawingEffect) = 0;

		virtual property InlineObjectMetrics Metrics 
		{
			InlineObjectMetrics get() = 0;
		}

		virtual property Managed::Graphics::DirectWrite::OverhangMetrics OverhangMetrics
		{
			Managed::Graphics::DirectWrite::OverhangMetrics get() = 0;
		}

		virtual property BreakCondition BreakConditionBefore
		{
			BreakCondition get() = 0;
		}

		virtual property BreakCondition BreakConditionAfter
		{
			BreakCondition get() = 0;
		}

	internal:
		IDWriteInlineObject* GetNative();
		IDWriteInlineObject* _native;
	};

	public ref class InlineObjectWrapper: public InlineObject
	{
	internal:
		InlineObjectWrapper(IDWriteInlineObject* native, bool addRef):
			InlineObject(native, addRef)
		{
		}
	public:
		virtual void Draw(
			ITextRenderer^ renderer, 
			Single originX, 
			Single originY, 
			Boolean isSideways, 
			Boolean isRtl, 
			ClientDrawingEffect^ clientDrawingEffect) override;

		virtual property InlineObjectMetrics Metrics
		{
			InlineObjectMetrics get() override;
		}

		virtual property Managed::Graphics::DirectWrite::OverhangMetrics OverhangMetrics
		{
			Managed::Graphics::DirectWrite::OverhangMetrics get() override;
		}

		virtual property BreakCondition BreakConditionBefore
		{
			BreakCondition get() override;
		}

		virtual property BreakCondition BreakConditionAfter
		{
			BreakCondition get() override;
		}
	};

	class __declspec(uuid("7265D85E-FABB-4BCC-98DA-E488BB3D1CA3")) 
		InlineObjectNative: public IDWriteInlineObject
	{
	public:
		InlineObjectNative(InlineObject^ managed): 
			_managed(managed), 
			_refCount(1)
		{
		}

		InlineObject^ GetObject()
		{
			return _managed;
		}

		STDMETHOD(Draw)(
			__maybenull void* clientDrawingContext,
			IDWriteTextRenderer* renderer,
			FLOAT originX,
			FLOAT originY,
			BOOL isSideways,
			BOOL isRightToLeft,
			__maybenull IUnknown* clientDrawingEffect
			);

		STDMETHOD(GetMetrics)(
			__out DWRITE_INLINE_OBJECT_METRICS* metrics
			);

		STDMETHOD(GetOverhangMetrics)(
			__out DWRITE_OVERHANG_METRICS* overhangs
			);

		STDMETHOD(GetBreakConditions)(
			__out DWRITE_BREAK_CONDITION* breakConditionBefore,
			__out DWRITE_BREAK_CONDITION* breakConditionAfter
			);

        unsigned long STDMETHODCALLTYPE AddRef();
        unsigned long STDMETHODCALLTYPE Release();
        HRESULT STDMETHODCALLTYPE QueryInterface(IID const& riid, void** ppvObject);
	private:
		gcroot<InlineObject^> _managed;
		LONG _refCount;
	};

}}}