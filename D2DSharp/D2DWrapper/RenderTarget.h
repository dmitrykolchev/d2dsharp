/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "DWCommon.h"
#include "D2DResource.h"
#include "Direct2DFactory.h"
#include "Bitmap.h"
#include "WicBitmapSource.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Graphics::DirectWrite;
using namespace Managed::Graphics::Imaging;

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	ref class TextFormat;
	ref class TextLayout;
	ref class GlyphRun;
}}}

namespace Managed { namespace Graphics { namespace Direct2D 
{
	ref class SolidColorBrush;
	ref class StrokeStyle;
	ref class Geometry;
	ref class Layer;
	ref class LayerParameters;
	ref class Mesh;
	ref class Bitmap;
	ref class BitmapBrush;
	ref class BitmapRenderTarget;	
	
	public enum class AntialiasMode  
	{
		PerPrimitive   = 0,
		Aliased        = 1 
	};

	public enum class TextAntialiasMode  
	{
		Default     = 0,
		ClearType   = 1,
		Grayscale   = 2,
		Aliased     = 3 
	};

	public enum class DrawTextOptions  
	{
		NoSnap   = 0x00000001,
		Clip     = 0x00000002,
		None     = 0x00000000 
	};


	[StructLayout(LayoutKind::Sequential)]
	public value struct DrawingStateDescription
	{
	private:
		AntialiasMode _antialiasMode;
		TextAntialiasMode _textAntialiasMode;
		System::UInt64 _tag1;
		System::UInt64 _tag2;
		Matrix3x2 _transform;
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct BitmapBrushProperties
	{
	private:
		ExtendMode _extendModeX;
		ExtendMode _extendModeY;
		BitmapInterpolationMode _interpolationMode;
	public:
		BitmapBrushProperties(ExtendMode extendModeX, ExtendMode extendModeY, BitmapInterpolationMode interpolationMode)
		{
			_extendModeX = extendModeX;
			_extendModeY = extendModeY;
			_interpolationMode = interpolationMode;
		}
	};

	public ref class RenderTarget: D2DResource
	{
	internal:
		RenderTarget(ID2D1RenderTarget* native): D2DResource(native)
		{
		}

	public:
		property Managed::Graphics::Direct2D::AntialiasMode AntialiasMode
		{
			Managed::Graphics::Direct2D::AntialiasMode get()
			{
				D2D1_ANTIALIAS_MODE mode = GetNative<ID2D1RenderTarget>()->GetAntialiasMode();
				return (Managed::Graphics::Direct2D::AntialiasMode)mode;
			}
			void set(Managed::Graphics::Direct2D::AntialiasMode value)
			{
				GetNative<ID2D1RenderTarget>()->SetAntialiasMode((D2D1_ANTIALIAS_MODE) value);
			}
		}

		property Managed::Graphics::Direct2D::TextAntialiasMode TextAntialiasMode
		{
			Managed::Graphics::Direct2D::TextAntialiasMode get()
			{
				D2D1_TEXT_ANTIALIAS_MODE mode = GetNative<ID2D1RenderTarget>()->GetTextAntialiasMode();
				return (Managed::Graphics::Direct2D::TextAntialiasMode)mode;
			}
			void set(Managed::Graphics::Direct2D::TextAntialiasMode value)
			{
				GetNative<ID2D1RenderTarget>()->SetTextAntialiasMode((D2D1_TEXT_ANTIALIAS_MODE) value);
			}
		}

		property Managed::Graphics::Direct2D::PixelFormat PixelFormat
		{
			Managed::Graphics::Direct2D::PixelFormat get()
			{
				return Managed::Graphics::Direct2D::PixelFormat(GetNative<ID2D1RenderTarget>()->GetPixelFormat());
			}
		}

		property SizeU PixelSize
		{
			SizeU get()
			{
				return SizeU(GetNative<ID2D1RenderTarget>()->GetPixelSize());
			}
		}

		property SizeF Size
		{
			SizeF get()
			{
				return SizeF(GetNative<ID2D1RenderTarget>()->GetSize());
			}
		}

		Boolean IsSupported(RenderTargetProperties renderTargetProperties)
		{
			return GetNative<ID2D1RenderTarget>()->IsSupported((D2D1_RENDER_TARGET_PROPERTIES *) &renderTargetProperties) ? true : false;
		}

		property Matrix3x2 Transform
		{
			Matrix3x2 get()
			{
				Matrix3x2 transform;
				GetNative<ID2D1RenderTarget>()->GetTransform((D2D1_MATRIX_3X2_F*) &transform);
				return transform;
			}
			void set(Matrix3x2 value)
			{
				GetNative<ID2D1RenderTarget>()->SetTransform((D2D1_MATRIX_3X2_F*) &value);
			}
		}

		property FLOAT DpiX
		{
			FLOAT get()
			{
				FLOAT dpiX;
				FLOAT dpiY;
				GetNative<ID2D1RenderTarget>()->GetDpi(&dpiX, &dpiY);
				return dpiX;
			}
			void set(FLOAT value)
			{
				GetNative<ID2D1RenderTarget>()->SetDpi(value, DpiY);
			}
		}
		property FLOAT DpiY
		{
			FLOAT get()
			{
				FLOAT dpiX;
				FLOAT dpiY;
				GetNative<ID2D1RenderTarget>()->GetDpi(&dpiX, &dpiY);
				return dpiY;
			}
			void set(FLOAT value)
			{
				GetNative<ID2D1RenderTarget>()->SetDpi(DpiX, value);
			}
		}

		property UInt32 MaximumBitmapSize
		{
			UInt32 get()
			{
				return (UInt32) GetNative<ID2D1RenderTarget>()->GetMaximumBitmapSize();
			}
		}

		void BeginDraw()
		{
			GetNative<ID2D1RenderTarget>()->BeginDraw();
		}

		Boolean EndDraw()
		{
			HRESULT hr = GetNative<ID2D1RenderTarget>()->EndDraw();
			if (hr == D2DERR_RECREATE_TARGET)
				return false;
			ComUtils::CheckResult(hr);
			return true;
		}

		void Clear(Color color)
		{
			GetNative<ID2D1RenderTarget>()->Clear(reinterpret_cast<D2D_COLOR_F*>(&color));
		}

		Bitmap^ CreateBitmap(SizeU size, IntPtr srcData, UInt32 pitch, BitmapProperties bitmapProperties);
		Bitmap^ CreateBitmap(SizeU size, array<Byte>^ srcData, UInt32 pitch, BitmapProperties bitmapProperties);
		Bitmap^ CreateBitmap(WicBitmapSource^ source, BitmapProperties bitmapProperties);
		Bitmap^ CreateBitmap(Type^ type, String^ resourceName);


		BitmapRenderTarget^ CreateCompatibleRenderTarget();
		BitmapRenderTarget^ CreateCompatibleRenderTarget(SizeF desiredSize);

		SolidColorBrush^ CreateSolidColorBrush(Color color, BrushProperties properties);
		
		SolidColorBrush^ CreateSolidColorBrush(Color color, FLOAT opacity, Matrix3x2 brushTransform)
		{
			return CreateSolidColorBrush(color, BrushProperties(opacity, brushTransform));
		}

		SolidColorBrush^ CreateSolidColorBrush(Color color, FLOAT opacity)
		{
			return CreateSolidColorBrush(color, BrushProperties(opacity, Matrix3x2::Identity));
		}

		SolidColorBrush^ CreateSolidColorBrush(Color color)
		{
			return CreateSolidColorBrush(color, BrushProperties::Default);
		}

		LinearGradientBrush^ CreateLinearGradientBrush(
			LinearGradientBrushProperties linearGradientBrushProperties,
			BrushProperties brushProperties,
			GradientStopCollection^ gradientStopCollection);
		
		RadialGradientBrush^ CreateRadialGradientBrush(
			RadialGradientBrushProperties radialGradientBrushProperties,
			BrushProperties brushProperties,
			GradientStopCollection^ gradientStopCollection);

		GradientStopCollection^ CreateGradientStopCollection(array<GradientStop>^ gradientStops);
		GradientStopCollection^ CreateGradientStopCollection(array<GradientStop>^ gradientStops, Gamma colorInterpolationGamma, ExtendMode extendMode);

		BitmapBrush^ CreateBitmapBrush(Bitmap^ bitmap, BitmapBrushProperties bitmapBrushProperties, BrushProperties brushProperties);

		BitmapBrush^ CreateGridPatternBrush(SizeF cellSize, Color gridColor);

		Layer^ CreateLayer();
		Layer^ CreateLayer(SizeF size);

		void PushLayer(LayerParameters^ layerParameters, Layer^ layer);
		
		void PopLayer()
		{
			GetNative<ID2D1RenderTarget>()->PopLayer();
		}

		void PushAxisAlignedClip(RectF clipRect, Managed::Graphics::Direct2D::AntialiasMode antialiasMode)
		{
			GetNative<ID2D1RenderTarget>()->PushAxisAlignedClip((D2D1_RECT_F *) &clipRect, (D2D1_ANTIALIAS_MODE) antialiasMode);
		}

		void PopAxisAlignedClip()
		{
			GetNative<ID2D1RenderTarget>()->PopAxisAlignedClip();
		}

		void DrawLine(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, PointF p0, PointF p1);
		void DrawLine(Brush^ brush, FLOAT strokeWidth, PointF p0, PointF p1);

		void FillMesh(Brush^ brush, Mesh^ mesh);

		void FillRect(Brush^ brush, RectF rect);
		void DrawRect(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, RectF rect);
		void DrawRect(Brush^ brush, FLOAT strokeWidth, RectF rect);

		void FillRoundedRect(Brush^ brush, RoundedRect rect);
		void DrawRoundedRect(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, RoundedRect rect);
		void DrawRoundedRect(Brush^ brush, FLOAT strokeWidth, RoundedRect rect);

		void FillEllipse(Brush^ brush, Ellipse ellipse);
		void DrawEllipse(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, Ellipse ellipse);
		void DrawEllipse(Brush^ brush, FLOAT strokeWidth, Ellipse ellipse);

		void FillGeometry(Brush^ brush, Brush^ opacityBrush, Geometry^ geometry);
		void FillGeometry(Brush^ brush, Geometry^ geometry);
		void DrawGeometry(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, Geometry^ geometry);
		void DrawGeometry(Brush^ brush, FLOAT strokeWidth, Geometry^ geometry);

		void DrawText(String^ string, TextFormat^ textFormat, RectF layoutRect, Brush^ brush, DrawTextOptions options, MeasuringMode measuringMode); 
		void DrawTextLayout(PointF origin, TextLayout^ textLayout, Brush^ brush, DrawTextOptions options);
		void DrawGlyphRun(PointF baselineOrigin, GlyphRun^ glyphRun, Brush^ foregroundBrush, MeasuringMode measuringMode);

		void DrawBitmap(Bitmap^ bitmap, RectF dstRect, Single opacity, BitmapInterpolationMode interpolationMode, RectF srcRect);
		void DrawBitmap(Bitmap^ bitmap, RectF dstRect, Single opacity, BitmapInterpolationMode interpolationMode);
	};
}}}