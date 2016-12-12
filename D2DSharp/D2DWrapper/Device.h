/*
* Device.h
*
* Authors:
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed {
	namespace Graphics {
		namespace Direct2D
		{
			public enum class DeviceContextOptions
			{
				None = D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
				EnableMultiThreadedOptimizations = D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS
			};
			/// <summary>
			/// This specifies the options while simultaneously creating the device, factory,
			/// and device context.
			/// </summary>
			[StructLayout(LayoutKind::Sequential)]
			public value struct CreationProperties
			{

				/// <summary>
				/// Describes locking behavior of D2D resources
				/// </summary>
				ThreadingMode ThreadingMode;
				DebugLevel DebugLevel;
				DeviceContextOptions Options;

			};

			ref class DeviceContext;
			ref class Managed::Graphics::Dxgi::DxgiDevice;


			public ref class Device : D2DResource
			{
			internal:
				Device(ID2D1Device *native) :
					D2DResource(native)
				{
				}
			public:
				//
				// Creates a new Direct2D device associated with the provided DXGI device.
				//
				static Device^ CreateDevice(DxgiDevice^ dxgiDevice, CreationProperties properties);
				//
				// Creates a new device context with no initially assigned target.
				//
				DeviceContext^ CreateDeviceContext(DeviceContextOptions options);

				//
				// Creates a D2D print control.
				//
				//STDMETHOD(CreatePrintControl)(
				//	_In_ IWICImagingFactory *wicFactory,
				//	_In_ IPrintDocumentPackageTarget *documentTarget,
				//	_In_opt_ CONST D2D1_PRINT_CONTROL_PROPERTIES *printControlProperties,
				//	_Outptr_ ID2D1PrintControl **printControl 
				//	) PURE;


				property Int64 MaximumTextureMemory
				{
					//
					// Gets the maximum amount of texture memory to maintain before evicting caches.
					//
					Int64 get()
					{
						return GetNative<ID2D1Device>()->GetMaximumTextureMemory();
					}
					//
					// Sets the maximum amount of texture memory to maintain before evicting caches.
					//
					void set(Int64 value)
					{
						GetNative<ID2D1Device>()->SetMaximumTextureMemory(value);
					}
				}
				//
				// Clears all resources that are cached but not held in use by the application
				// through an interface reference.
				//
				void ClearResources()
				{
					GetNative<ID2D1Device>()->ClearResources();
				}
			};

			public ref class ColorContext : D2DResource
			{
			internal:
				ColorContext(ID2D1ColorContext* native) :
					D2DResource(native)
				{
				}
			};

			public ref class GdiMetafile : ComWrapper
			{
			internal:
				GdiMetafile(ID2D1GdiMetafile* native) : ComWrapper(native)
				{
				}
			public:
				property RectF Bounds
				{
					RectF get() {
						RectF bounds;
						ComUtils::CheckResult(GetNative<ID2D1GdiMetafile>()->GetBounds((D2D1_RECT_F*) &bounds));
						return bounds;
					}
				}
				// TODO: Stream
				// void Stream(GdiMetafileSink^ sink);
			};

			public interface class ICommandSink
			{
			public:
				void BeginDraw();
				void Clear(Color color);
				void DrawGeometry(Geometry^ geometry, Brush^ brush, FLOAT strokeWidth, StrokeStyle^ strokeStyle);
				//void DrawGlyphRun(PointF baselineOrigin, ...)
				void DrawImage(Image^ image, PointF targetOffset, RectF imageRectangle, InterpolationMode interpolationMode, CompositeMode compsiteMode);
				void DrawLine(PointF point0, PointF point1, Brush^ brush, FLOAT strokeWidth, StrokeStyle^ strokeStyle);
				void DrawRectangle(RectF rect, Brush^ brush, FLOAT strokeWidth, StrokeStyle^ strokeStyle);
				void EndDraw();
				void FillGeometry(Geometry^ geometry, Brush^ brush, Brush^ opacityBrush);
				void FillMesh(Mesh^ mesh, Brush^ brush);
				void FillOpacityMask(Bitmap^ opacityMask, Brush^ brush, RectF destinationRect, RectF sourceRect);
				void FillRectangle(RectF rect, Brush^ brush);
				void DrawBitmap(Bitmap^ bitmap, RectF destinationRect, FLOAT opacity, InterpolationMode interpolationMode, RectF sourceRect, Matrix4x4 perspectiveTransform);
				void DrawGdiMetafile(GdiMetafile^ metafile, PointF targetOffset);
				void PopAxisAlignedClip();
				void PopLayer();
				void PushAxisAlignedClip(RectF clipRect, AntialiasMode antialiasMode);
				//void PushLayer()
				void SetAntialisMode(AntialiasMode antialiasMode);
				void SetPrimitiveBlend(PrimitiveBlend primitiveBlend);
				void SetTags(UInt64 tag1, UInt64 tag2);
				void SetTextAntialiasMode(TextAntialiasMode textAntialiasMode);
				void SetTextRenderingParams(Managed::Graphics::DirectWrite::RenderingParams^ renderingParams);
				void SetTransoform(Matrix3x2 transform);
				void SetUnitMode(UnitMode unitMode);

			};

			class CustomCommandSink : public ID2D1CommandSink
			{
			public:
				CustomCommandSink(ICommandSink^ sink) : _refCount(1), _sink(sink)
				{
				}
				STDMETHOD(BeginDraw)();
				STDMETHOD(EndDraw)();
				STDMETHOD(SetAntialiasMode)(
					D2D1_ANTIALIAS_MODE antialiasMode
					);

				STDMETHOD(SetTags)(
					D2D1_TAG tag1,
					D2D1_TAG tag2
					);

				STDMETHOD(SetTextAntialiasMode)(
					D2D1_TEXT_ANTIALIAS_MODE textAntialiasMode
					);

				STDMETHOD(SetTextRenderingParams)(
					_In_opt_ IDWriteRenderingParams *textRenderingParams
					);

				STDMETHOD(SetTransform)(
					_In_ CONST D2D1_MATRIX_3X2_F *transform
					);

				STDMETHOD(SetPrimitiveBlend)(
					D2D1_PRIMITIVE_BLEND primitiveBlend
					);

				STDMETHOD(SetUnitMode)(
					D2D1_UNIT_MODE unitMode
					);

				STDMETHOD(Clear)(
					_In_opt_ CONST D2D1_COLOR_F *color
					);

				STDMETHOD(DrawGlyphRun)(
					D2D1_POINT_2F baselineOrigin,
					_In_ CONST DWRITE_GLYPH_RUN *glyphRun,
					_In_opt_ CONST DWRITE_GLYPH_RUN_DESCRIPTION *glyphRunDescription,
					_In_ ID2D1Brush *foregroundBrush,
					DWRITE_MEASURING_MODE measuringMode
					);

				STDMETHOD(DrawLine)(
					D2D1_POINT_2F point0,
					D2D1_POINT_2F point1,
					_In_ ID2D1Brush *brush,
					FLOAT strokeWidth,
					_In_opt_ ID2D1StrokeStyle *strokeStyle
					);

				STDMETHOD(DrawGeometry)(
					_In_ ID2D1Geometry *geometry,
					_In_ ID2D1Brush *brush,
					FLOAT strokeWidth,
					_In_opt_ ID2D1StrokeStyle *strokeStyle
					);

				STDMETHOD(DrawRectangle)(
					_In_ CONST D2D1_RECT_F *rect,
					_In_ ID2D1Brush *brush,
					FLOAT strokeWidth,
					_In_opt_ ID2D1StrokeStyle *strokeStyle
					);

				STDMETHOD(DrawBitmap)(
					_In_ ID2D1Bitmap *bitmap,
					_In_opt_ CONST D2D1_RECT_F *destinationRectangle,
					FLOAT opacity,
					D2D1_INTERPOLATION_MODE interpolationMode,
					_In_opt_ CONST D2D1_RECT_F *sourceRectangle,
					_In_opt_ CONST D2D1_MATRIX_4X4_F *perspectiveTransform
					);

				STDMETHOD(DrawImage)(
					_In_ ID2D1Image *image,
					_In_opt_ CONST D2D1_POINT_2F *targetOffset,
					_In_opt_ CONST D2D1_RECT_F *imageRectangle,
					D2D1_INTERPOLATION_MODE interpolationMode,
					D2D1_COMPOSITE_MODE compositeMode
					);

				STDMETHOD(DrawGdiMetafile)(
					_In_ ID2D1GdiMetafile *gdiMetafile,
					_In_opt_ CONST D2D1_POINT_2F *targetOffset
					);

				STDMETHOD(FillMesh)(
					_In_ ID2D1Mesh *mesh,
					_In_ ID2D1Brush *brush
					);

				STDMETHOD(FillOpacityMask)(
					_In_ ID2D1Bitmap *opacityMask,
					_In_ ID2D1Brush *brush,
					_In_opt_ CONST D2D1_RECT_F *destinationRectangle,
					_In_opt_ CONST D2D1_RECT_F *sourceRectangle
					);

				STDMETHOD(FillGeometry)(
					_In_ ID2D1Geometry *geometry,
					_In_ ID2D1Brush *brush,
					_In_opt_ ID2D1Brush *opacityBrush
					);

				STDMETHOD(FillRectangle)(
					_In_ CONST D2D1_RECT_F *rect,
					_In_ ID2D1Brush *brush
					);

				STDMETHOD(PushAxisAlignedClip)(
					_In_ CONST D2D1_RECT_F *clipRect,
					D2D1_ANTIALIAS_MODE antialiasMode
					);

				STDMETHOD(PushLayer)(
					_In_ CONST D2D1_LAYER_PARAMETERS1 *layerParameters1,
					_In_opt_ ID2D1Layer *layer
					);

				STDMETHOD(PopAxisAlignedClip)(
					);

				STDMETHOD(PopLayer)(
					);
				unsigned long STDMETHODCALLTYPE AddRef();
				unsigned long STDMETHODCALLTYPE Release();
				HRESULT STDMETHODCALLTYPE QueryInterface(
					IID const& riid,
					void** ppvObject
					);
			protected:
				virtual ~CustomCommandSink() { }
			private:
				gcroot<ICommandSink^> _sink;
				LONG _refCount;
			};

			public ref class CommandList : Image
			{
			internal:
				CommandList(ID2D1CommandList* native) :
					Image(native)
				{
				}
			public:
				void Close()
				{
					ComUtils::CheckResult(GetNative<ID2D1CommandList>()->Close());
				}
				void Stream(ICommandSink^ sink)
				{
					CustomCommandSink *customSink = new CustomCommandSink(sink);
					try
					{
						ComUtils::CheckResult(GetNative<ID2D1CommandList>()->Stream(customSink));
					}
					finally
					{
						customSink->Release();
					}
				}
			};

			public ref class DeviceContext : RenderTarget
			{
			internal:
				DeviceContext(ID2D1DeviceContext* native) :
					RenderTarget(native)
				{
				}
			public:
				//
				// Creates a bitmap with extended bitmap properties, potentially from a block of
				// memory.
				//
				Bitmap1^ CreateBitmap(SizeU size, array<Byte>^ srcData, UInt32 pitch, BitmapProperties^ bitmapProperties, BitmapOptions options, ColorContext^ colorContext);
				Bitmap1^ CreateBitmapFromWicBitmap(WicBitmapSource^ source);
				Bitmap1^ DeviceContext::CreateBitmapFromWicBitmap(WicBitmapSource^ source, BitmapProperties^ bitmapProperties, BitmapOptions options, ColorContext^ colorContext);

				CommandList^ CreateCommandList() {
					ID2D1CommandList* commandList;
					ComUtils::CheckResult(GetNative<ID2D1DeviceContext>()->CreateCommandList(&commandList));
					return gcnew CommandList(commandList);
				}

				Bitmap1^ CreateBitmapFromDxgiSurface(DxgiSurface^ dxgiSurface, BitmapProperties^ bitmapProperties);
				Bitmap1^ CreateBitmapFromDxgiSurface(DxgiSurface^ dxgiSurface);
				void SetTarget(Image^ bitmap);
		
				//
				// Draw an image to the device context. The image represents either a concrete
				// bitmap or the output of an effect graph.
				//
				void DrawImage(Image^ image)
				{
					GetNative<ID2D1DeviceContext>()->DrawImage(
						image->GetNative<ID2D1Image>(),
						nullptr,
						nullptr,
						D2D1_INTERPOLATION_MODE_LINEAR,
						D2D1_COMPOSITE_MODE_SOURCE_OVER
					);
				}
				//
				// Draw an image to the device context. The image represents either a concrete
				// bitmap or the output of an effect graph.
				//
				void DrawImage(Image^ image, InterpolationMode interpolationMode, CompositeMode compositeMode)
				{
					GetNative<ID2D1DeviceContext>()->DrawImage(
						image->GetNative<ID2D1Image>(),
						nullptr,
						nullptr,
						(D2D1_INTERPOLATION_MODE)interpolationMode,
						(D2D1_COMPOSITE_MODE)compositeMode
					);
				}
				//
				// Draw an image to the device context. The image represents either a concrete
				// bitmap or the output of an effect graph.
				//
				void DrawImage(Image^ image, PointF targetOffset)
				{
					GetNative<ID2D1DeviceContext>()->DrawImage(
						image->GetNative<ID2D1Image>(),
						reinterpret_cast<D2D1_POINT_2F*>(&targetOffset),
						nullptr,
						D2D1_INTERPOLATION_MODE_LINEAR,
						D2D1_COMPOSITE_MODE_SOURCE_OVER
					);
				}
				//
				// Draw an image to the device context. The image represents either a concrete
				// bitmap or the output of an effect graph.
				//
				void DrawImage(Image^ image, PointF targetOffset, RectF imageRectangle, InterpolationMode interpolationMode, CompositeMode compositeMode)
				{
					GetNative<ID2D1DeviceContext>()->DrawImage(
						image->GetNative<ID2D1Image>(),
						reinterpret_cast<D2D1_POINT_2F*>(&targetOffset),
						reinterpret_cast<D2D1_RECT_F*>(&imageRectangle),
						(D2D1_INTERPOLATION_MODE)interpolationMode,
						(D2D1_COMPOSITE_MODE)compositeMode
					);
				}
				//
				// Draws a bitmap to the render target.
				//
				void DrawBitmap(Bitmap^ bitmap, FLOAT opacity, InterpolationMode interpolationMode)
				{
					GetNative<ID2D1DeviceContext>()->DrawBitmap(
						bitmap->GetNative<ID2D1Bitmap>(),
						nullptr,
						opacity,
						(D2D1_INTERPOLATION_MODE)interpolationMode,
						nullptr,
						nullptr
					);
				}
				//
				// Draws a bitmap to the render target.
				//
				void DrawBitmap(Bitmap^ bitmap, RectF destinationRectangle, FLOAT opacity, InterpolationMode interpolationMode, RectF sourceRectangle, Matrix4x4 transform)
				{
					GetNative<ID2D1DeviceContext>()->DrawBitmap(
						bitmap->GetNative<ID2D1Bitmap>(),
						reinterpret_cast<D2D1_RECT_F*>(&destinationRectangle),
						opacity,
						(D2D1_INTERPOLATION_MODE)interpolationMode,
						reinterpret_cast<D2D1_RECT_F*>(&sourceRectangle),
						reinterpret_cast<D2D1_MATRIX_4X4_F*>(&transform)
					);
				}
				//
				// Draws a bitmap to the render target.
				//
				void DrawBitmap(Bitmap^ bitmap, RectF destinationRectangle, FLOAT opacity, InterpolationMode interpolationMode)
				{
					GetNative<ID2D1DeviceContext>()->DrawBitmap(
						bitmap->GetNative<ID2D1Bitmap>(),
						reinterpret_cast<D2D1_RECT_F*>(&destinationRectangle),
						opacity,
						(D2D1_INTERPOLATION_MODE)interpolationMode,
						nullptr,
						nullptr
					);
				}
			};
		}
	}
}