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
	interface class ITextRenderer;

	class CustomTextRenderer: public IDWriteTextRenderer
	{
	public:
		CustomTextRenderer(ITextRenderer^ managedRenderer): 
			_managedRenderer(managedRenderer),
			_refCount(1)
		{
		}
	public:
		STDMETHOD(IsPixelSnappingDisabled)(
			__maybenull void* clientDrawingContext,
			__out BOOL* isDisabled
			);
		STDMETHOD(GetCurrentTransform)(
			__maybenull void* clientDrawingContext,
			__out DWRITE_MATRIX* transform
			);
		STDMETHOD(GetPixelsPerDip)(
			__maybenull void* clientDrawingContext,
			__out FLOAT* pixelsPerDip
			);
		STDMETHOD(DrawGlyphRun)(
			__maybenull void* clientDrawingContext,
			FLOAT baselineOriginX,
			FLOAT baselineOriginY,
			DWRITE_MEASURING_MODE measuringMode,
			__in DWRITE_GLYPH_RUN const* glyphRun,
			__in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
			__maybenull IUnknown* clientDrawingEffect
			);
		STDMETHOD(DrawUnderline)(
			__maybenull void* clientDrawingContext,
			FLOAT baselineOriginX,
			FLOAT baselineOriginY,
			__in DWRITE_UNDERLINE const* underline,
			__maybenull IUnknown* clientDrawingEffect
			);
		STDMETHOD(DrawStrikethrough)(
			__maybenull void* clientDrawingContext,
			FLOAT baselineOriginX,
			FLOAT baselineOriginY,
			__in DWRITE_STRIKETHROUGH const* strikethrough,
			__maybenull IUnknown* clientDrawingEffect
			);
		STDMETHOD(DrawInlineObject)(
			__maybenull void* clientDrawingContext,
			FLOAT originX,
			FLOAT originY,
			IDWriteInlineObject* inlineObject,
			BOOL isSideways,
			BOOL isRightToLeft,
			__maybenull IUnknown* clientDrawingEffect
			);
    public:
        unsigned long STDMETHODCALLTYPE AddRef();
        unsigned long STDMETHODCALLTYPE Release();
        HRESULT STDMETHODCALLTYPE QueryInterface(
            IID const& riid,
            void** ppvObject
        );

    protected:
        virtual ~CustomTextRenderer() { }

	private:
		gcroot<ITextRenderer^> _managedRenderer;
		LONG _refCount;
	};
}}}