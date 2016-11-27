#include "Stdafx.h"
#include "Device.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed {
	namespace Graphics {
		namespace Direct2D
		{
			DeviceContext^ Device::CreateDeviceContext(DeviceContextOptions options)
			{
				ID2D1DeviceContext* deviceContext;
				ComUtils::CheckResult(GetNative<ID2D1Device>()->CreateDeviceContext((D2D1_DEVICE_CONTEXT_OPTIONS) options, &deviceContext));
				return gcnew DeviceContext(deviceContext);
			}

			Bitmap1^ DeviceContext::CreateBitmap(SizeU size, array<Byte>^ srcData, UInt32 pitch, BitmapProperties^ bitmapProperties, BitmapOptions options, ColorContext^ colorContext)
			{
				pin_ptr<Byte> p = &srcData[0];
				ID2D1ColorContext* colorContextPtr = colorContext == nullptr ? nullptr : colorContext->GetNative<ID2D1ColorContext>();
				D2D1_BITMAP_PROPERTIES1 bitmapProperties1 = D2D1::BitmapProperties1(
					(D2D1_BITMAP_OPTIONS) options,
					*(D2D1_PIXEL_FORMAT*) &bitmapProperties->Format,
					bitmapProperties->DpiX,
					bitmapProperties->DpiY,
					colorContextPtr);
				ID2D1Bitmap1* bitmap;
				ComUtils::CheckResult(GetNative<ID2D1DeviceContext>()->CreateBitmap(
					*(D2D1_SIZE_U*) &size,
					p,
					pitch,
					&bitmapProperties1,
					&bitmap));
				return gcnew Bitmap1(bitmap);
			}

			unsigned long STDMETHODCALLTYPE CustomCommandSink::AddRef()
			{
				return InterlockedIncrement(&_refCount);
			}

			unsigned long STDMETHODCALLTYPE CustomCommandSink::Release()
			{
				if (InterlockedDecrement(&_refCount) == 0)
				{
					delete this;
					return 0;
				}
				return _refCount;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::QueryInterface(IID const& riid, void** ppvObject)
			{
				if (__uuidof(ID2D1SimplifiedGeometrySink) == riid)
				{
					*ppvObject = static_cast<ID2D1CommandSink*>(this);
				}
				else if (__uuidof(IUnknown) == riid)
				{
					*ppvObject = static_cast<IUnknown*>(this);
				}
				else
				{
					*ppvObject = NULL;
					return E_NOINTERFACE;
				}
				return S_OK;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::BeginDraw()
			{
				return E_NOTIMPL;
			}
			HRESULT STDMETHODCALLTYPE CustomCommandSink::EndDraw()
			{
				return E_NOTIMPL;
			}
			HRESULT STDMETHODCALLTYPE CustomCommandSink::SetAntialiasMode(
				D2D1_ANTIALIAS_MODE antialiasMode
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::SetTags(
				D2D1_TAG tag1,
				D2D1_TAG tag2
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::SetTextAntialiasMode(
				D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::SetTextRenderingParams(
				_In_opt_ IDWriteRenderingParams *textRenderingParams
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::SetTransform(
				_In_ CONST D2D1_MATRIX_3X2_F *transform
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::SetPrimitiveBlend(
				D2D1_PRIMITIVE_BLEND primitiveBlend
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::SetUnitMode(
				D2D1_UNIT_MODE unitMode
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::Clear(
				_In_opt_ CONST D2D1_COLOR_F *color
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::DrawGlyphRun(
				D2D1_POINT_2F baselineOrigin,
				_In_ CONST DWRITE_GLYPH_RUN *glyphRun,
				_In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION *glyphRunDescription,
				_In_ ID2D1Brush *foregroundBrush,
				DWRITE_MEASURING_MODE measuringMode
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::DrawLine(
				D2D1_POINT_2F point0,
				D2D1_POINT_2F point1,
				_In_ ID2D1Brush *brush,
				FLOAT strokeWidth,
				_In_opt_ ID2D1StrokeStyle *strokeStyle
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::DrawGeometry(
				_In_ ID2D1Geometry *geometry,
				_In_ ID2D1Brush *brush,
				FLOAT strokeWidth,
				_In_opt_ ID2D1StrokeStyle *strokeStyle
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::DrawRectangle(
				_In_ CONST D2D1_RECT_F *rect,
				_In_ ID2D1Brush *brush,
				FLOAT strokeWidth,
				_In_opt_ ID2D1StrokeStyle *strokeStyle
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::DrawBitmap(
				_In_ ID2D1Bitmap *bitmap,
				_In_opt_ CONST D2D1_RECT_F *destinationRectangle,
				FLOAT opacity,
				D2D1_INTERPOLATION_MODE interpolationMode,
				_In_opt_ CONST D2D1_RECT_F *sourceRectangle,
				_In_opt_ CONST D2D1_MATRIX_4X4_F *perspectiveTransform
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::DrawImage(
				_In_ ID2D1Image *image,
				_In_opt_ CONST D2D1_POINT_2F *targetOffset,
				_In_opt_ CONST D2D1_RECT_F *imageRectangle,
				D2D1_INTERPOLATION_MODE interpolationMode,
				D2D1_COMPOSITE_MODE compositeMode
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::DrawGdiMetafile(
				_In_ ID2D1GdiMetafile *gdiMetafile,
				_In_opt_ CONST D2D1_POINT_2F *targetOffset
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::FillMesh(
				_In_ ID2D1Mesh *mesh,
				_In_ ID2D1Brush *brush
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::FillOpacityMask(
				_In_ ID2D1Bitmap *opacityMask,
				_In_ ID2D1Brush *brush,
				_In_opt_ CONST D2D1_RECT_F *destinationRectangle,
				_In_opt_ CONST D2D1_RECT_F *sourceRectangle
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::FillGeometry(
				_In_ ID2D1Geometry *geometry,
				_In_ ID2D1Brush *brush,
				_In_opt_ ID2D1Brush *opacityBrush
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::FillRectangle(
				_In_ CONST D2D1_RECT_F *rect,
				_In_ ID2D1Brush *brush
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::PushAxisAlignedClip(
				_In_ CONST D2D1_RECT_F *clipRect,
				D2D1_ANTIALIAS_MODE antialiasMode
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::PushLayer(
				_In_ CONST D2D1_LAYER_PARAMETERS1 *layerParameters1,
				_In_opt_ ID2D1Layer *layer
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::PopAxisAlignedClip(
				)
			{
				return E_NOTIMPL;
			}

			HRESULT STDMETHODCALLTYPE CustomCommandSink::PopLayer()
			{
				return E_NOTIMPL;
			}

		}
	}
}