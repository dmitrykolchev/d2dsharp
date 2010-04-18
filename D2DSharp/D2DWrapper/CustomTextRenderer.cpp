/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

using namespace Managed::Graphics::Direct2D;
using namespace Managed::Graphics::DirectWrite;

HRESULT STDMETHODCALLTYPE CustomTextRenderer::IsPixelSnappingDisabled(
	__maybenull void* clientDrawingContext,
	__out BOOL* isDisabled
	)
{
	try
	{
		Boolean pixelSnappingDisabled = _managedRenderer->IsPixelSnappingDisabled;
		*isDisabled = pixelSnappingDisabled != false;
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CustomTextRenderer::GetCurrentTransform(
	__maybenull void* clientDrawingContext,
	__out DWRITE_MATRIX* transform
	)
{
	try
	{
		Matrix3x2 matrix = _managedRenderer->CurrentTransform;
		transform->m11 = matrix.M11;
		transform->m12 = matrix.M12;
		transform->m21 = matrix.M21;
		transform->m22 = matrix.M22;
		transform->dx = matrix.M31;
		transform->dy = matrix.M32;
	}
	catch(Exception^)
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CustomTextRenderer::GetPixelsPerDip(
	__maybenull void* clientDrawingContext,
	__out FLOAT* pixelsPerDip
	)
{
	try
	{
		*pixelsPerDip = _managedRenderer->PixelsPerDip;
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CustomTextRenderer::DrawGlyphRun(
	__maybenull void* clientDrawingContext,
	FLOAT baselineOriginX,
	FLOAT baselineOriginY,
	DWRITE_MEASURING_MODE measuringMode,
	__in DWRITE_GLYPH_RUN const* glyphRun,
	__in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
	__maybenull IUnknown* clientDrawingEffect
	)
{
	try
	{
		GlyphRun^ mglyphRun = gcnew GlyphRun(glyphRun);
		GlyphRunDescription^ mglyphRunDescription = gcnew GlyphRunDescription(glyphRunDescription);
		ClientDrawingEffect^ drawingEffect = nullptr;
		if(clientDrawingEffect)
		{
			ClientDrawingEffectNative* native = NULL;
			ComUtils::CheckResult(clientDrawingEffect->QueryInterface(__uuidof(ClientDrawingEffectNative), (void**)&native));
			drawingEffect = native->GetObject();
		}
		try
		{
			_managedRenderer->DrawGlyphRun(baselineOriginX, baselineOriginY, (MeasuringMode)measuringMode, 
				mglyphRun,
				mglyphRunDescription,
				drawingEffect);
		}
		finally
		{
			if(drawingEffect != nullptr)
				delete drawingEffect;
			delete mglyphRunDescription;
			delete mglyphRun;
		}
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CustomTextRenderer::DrawUnderline(
	__maybenull void* clientDrawingContext,
	FLOAT baselineOriginX,
	FLOAT baselineOriginY,
	__in DWRITE_UNDERLINE const* underline,
	__maybenull IUnknown* clientDrawingEffect
	)
{
	try
	{
		Underline^ mUnderline = gcnew Underline(underline);
		ClientDrawingEffect^ drawingEffect = nullptr;
		if(clientDrawingEffect)
		{
			ClientDrawingEffectNative* native = NULL;
			ComUtils::CheckResult(clientDrawingEffect->QueryInterface(__uuidof(ClientDrawingEffectNative), (void**)&native));
			drawingEffect = native->GetObject();
		}
		try
		{
			_managedRenderer->DrawUnderline(baselineOriginX, baselineOriginY, mUnderline, drawingEffect);
		}
		finally
		{
			if(drawingEffect != nullptr)
				delete drawingEffect;
			delete mUnderline;
		}
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CustomTextRenderer::DrawStrikethrough(
	__maybenull void* clientDrawingContext,
	FLOAT baselineOriginX,
	FLOAT baselineOriginY,
	__in DWRITE_STRIKETHROUGH const* strikethrough,
	__maybenull IUnknown* clientDrawingEffect
	)
{
	try
	{
		Strikethrough^ mStrikethrough = gcnew Strikethrough(strikethrough);
		ClientDrawingEffect^ drawingEffect = nullptr;
		if(clientDrawingEffect)
		{
			ClientDrawingEffectNative* native = NULL;
			ComUtils::CheckResult(clientDrawingEffect->QueryInterface(__uuidof(ClientDrawingEffectNative), (void**)&native));
			drawingEffect = native->GetObject();
		}
		try
		{
			_managedRenderer->DrawStrikethrough(baselineOriginX, baselineOriginY, mStrikethrough, drawingEffect);
		}
		finally
		{
			if(drawingEffect != nullptr)
				delete drawingEffect;
			delete mStrikethrough;
		}
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CustomTextRenderer::DrawInlineObject(
	__maybenull void* clientDrawingContext,
	FLOAT originX,
	FLOAT originY,
	IDWriteInlineObject* inlineObject,
	BOOL isSideways,
	BOOL isRightToLeft,
	__maybenull IUnknown* clientDrawingEffect
	)
{
	try
	{
		InlineObject ^mInlineObject = gcnew InlineObject(inlineObject, true);
		ClientDrawingEffect^ drawingEffect = nullptr;
		if(clientDrawingEffect)
		{
			ClientDrawingEffectNative* native = NULL;
			ComUtils::CheckResult(clientDrawingEffect->QueryInterface(__uuidof(ClientDrawingEffectNative), (void**)&native));
			drawingEffect = native->GetObject();
		}
		try
		{
			_managedRenderer->DrawInlineObject(
				originX, 
				originY, 
				mInlineObject, 
				isSideways != 0, 
				isRightToLeft != 0, 
				drawingEffect);
		}
		finally
		{
			if(drawingEffect != nullptr)
				delete drawingEffect;
			delete mInlineObject;
		}
	}
	catch(Exception^)
	{
		return E_FAIL;
	}
	return S_OK;
}

unsigned long STDMETHODCALLTYPE CustomTextRenderer::AddRef()
{
    return InterlockedIncrement(&_refCount);
}

unsigned long STDMETHODCALLTYPE CustomTextRenderer::Release()
{
    if (InterlockedDecrement(&_refCount) == 0)
    {
        delete this;
        return 0;
    }
    return _refCount;
}

HRESULT STDMETHODCALLTYPE CustomTextRenderer::QueryInterface(IID const& riid, void** ppvObject)
{
    if (__uuidof(IDWriteTextRenderer) == riid)
    {
        *ppvObject = static_cast<IDWriteTextRenderer*>(this);
    }
	else if(__uuidof(IDWritePixelSnapping) == riid)
    {
        *ppvObject = static_cast<IDWritePixelSnapping*>(this);
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
