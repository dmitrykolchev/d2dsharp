/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "stdafx.h"

#include "RenderTarget.h"
#include "SolidColorBrush.h"
#include "TextFormat.h"
#include "WicBitmapSource.h"


using namespace Managed::Graphics::DirectWrite;
using namespace Managed::Graphics::Imaging;
using namespace Managed::Graphics::Imaging;

namespace Managed { namespace Graphics { namespace Direct2D
{

	void RenderTarget::FillRect(Brush^ brush, RectF rect)
	{
		GetNative()->FillRectangle(reinterpret_cast<D2D1_RECT_F*>(&rect), brush->GetNative());
	}

	void RenderTarget::DrawRect(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, RectF rect)
	{
		GetNative()->DrawRectangle((D2D1_RECT_F*)&rect, brush->GetNative(), strokeWidth, style->GetNative());
	}

	void RenderTarget::DrawRect(Brush^ brush, FLOAT strokeWidth, RectF rect)
	{
		GetNative()->DrawRectangle((D2D1_RECT_F*)&rect, brush->GetNative(), strokeWidth, NULL);
	}
	
	void RenderTarget::FillRoundedRect(Brush^ brush, RoundedRect rect)
	{
		GetNative()->FillRoundedRectangle(reinterpret_cast<D2D1_ROUNDED_RECT*>(&rect), brush->GetNative());
	}

	void RenderTarget::DrawRoundedRect(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, RoundedRect rect)
	{
		GetNative()->DrawRoundedRectangle((D2D1_ROUNDED_RECT*)&rect, brush->GetNative(), strokeWidth, style->GetNative());
	}

	void RenderTarget::DrawRoundedRect(Brush^ brush, FLOAT strokeWidth, RoundedRect rect)
	{
		GetNative()->DrawRoundedRectangle((D2D1_ROUNDED_RECT*)&rect, brush->GetNative(), strokeWidth, NULL);
	}
	
	void RenderTarget::FillEllipse(Brush^ brush, Ellipse ellipse)
	{
		GetNative()->FillEllipse(reinterpret_cast<D2D1_ELLIPSE*>(&ellipse), brush->GetNative());
	}

	void RenderTarget::DrawEllipse(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, Ellipse ellipse)
	{
		GetNative()->DrawEllipse((D2D1_ELLIPSE*)&ellipse, brush->GetNative(), strokeWidth, style->GetNative());
	}

	void RenderTarget::DrawEllipse(Brush^ brush, FLOAT strokeWidth, Ellipse ellipse)
	{
		GetNative()->DrawEllipse((D2D1_ELLIPSE*)&ellipse, brush->GetNative(), strokeWidth, NULL);
	}
	
	void RenderTarget::DrawLine(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, PointF p0, PointF p1)
	{
		GetNative()->DrawLine(*(D2D1_POINT_2F*)&p0, *(D2D1_POINT_2F*)&p1, brush->GetNative(), strokeWidth, style->GetNative());
	}

	void RenderTarget::DrawLine(Brush^ brush, FLOAT strokeWidth, PointF p0, PointF p1)
	{
		GetNative()->DrawLine(*(D2D1_POINT_2F*)&p0, *(D2D1_POINT_2F*)&p1, brush->GetNative(), strokeWidth, NULL);
	}

	Bitmap^ RenderTarget::CreateBitmap(SizeU size, IntPtr srcData, UInt32 pitch, BitmapProperties bitmapProperties)
	{
		ID2D1Bitmap *bitmap;

		HRESULT hr = GetNative()->CreateBitmap(
			*(D2D1_SIZE_U*)&size, 
			srcData.ToPointer(), 
			pitch, 
			(D2D1_BITMAP_PROPERTIES *)&bitmapProperties,
			&bitmap);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew Bitmap(bitmap);
	}

	Bitmap^ RenderTarget::CreateBitmap(SizeU size, array<Byte>^ srcData, UInt32 pitch, BitmapProperties bitmapProperties)
	{
		pin_ptr<Byte> p = &srcData[0];

		ID2D1Bitmap *bitmap;

		HRESULT hr = GetNative()->CreateBitmap(
			*(D2D1_SIZE_U*)&size, 
			p, 
			pitch, 
			(D2D1_BITMAP_PROPERTIES *)&bitmapProperties,
			&bitmap);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew Bitmap(bitmap);
	}

	Bitmap^ RenderTarget::CreateBitmap(WicBitmapSource^ source, BitmapProperties bitmapProperties)
	{
		ID2D1Bitmap *bitmap;

		HRESULT hr = GetNative()->CreateBitmapFromWicBitmap(
			source->GetNative(),
			(D2D1_BITMAP_PROPERTIES *)&bitmapProperties,
			&bitmap);

		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew Bitmap(bitmap);
	}

	Bitmap^ RenderTarget::CreateBitmap(Type^ type, String^ resourceName)
	{
		WicImagingFactory^ imagingFactory = WicImagingFactory::Create();
		try
		{
			WicStream^ stream = imagingFactory->CreateStream();
			try
			{
				stream->Initialize(type, resourceName);
				WicBitmapDecoder^ decoder = imagingFactory->CreateDecoder(stream, Guid::Empty, DecodeOptions::MetadataCacheOnDemand);
				try
				{
					WicBitmapFrameDecode^ frame = decoder->GetFrame(0);
					try
					{
						WicFormatConverter^ converter = imagingFactory->CreateFormatConverter();
						try 
						{
							converter->Convert(frame, WicPixelFormats::PixelFormat32bppPBGRA, BitmapDitherType::None, nullptr, 0, BitmapPaletteType::Custom);
							BitmapProperties bitmapProperties = BitmapProperties();
							return CreateBitmap(converter, bitmapProperties);
						}
						finally 
						{
							delete converter;
						}
					}
					finally
					{
						delete frame;
					}
				}
				finally
				{
					delete decoder;
				}
			}
			finally
			{
				delete stream;
			}
		}
		finally
		{
			delete imagingFactory;
		}
	}

	BitmapRenderTarget^ RenderTarget::CreateCompatibleRenderTarget()
	{
		ID2D1BitmapRenderTarget *bitmapRenderTarget;
		HRESULT hr = GetNative()->CreateCompatibleRenderTarget(&bitmapRenderTarget);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew BitmapRenderTarget(bitmapRenderTarget);
	}

	BitmapRenderTarget^ RenderTarget::CreateCompatibleRenderTarget(SizeF desiredSize)
	{
		ID2D1BitmapRenderTarget *bitmapRenderTarget;
		HRESULT hr = GetNative()->CreateCompatibleRenderTarget(*(D2D1_SIZE_F*)&desiredSize, &bitmapRenderTarget);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew BitmapRenderTarget(bitmapRenderTarget);
	}

	SolidColorBrush^ RenderTarget::CreateSolidColorBrush(Color color, BrushProperties properties)
	{
		ID2D1SolidColorBrush *solidColorBrush;
		HRESULT hr = GetNative()->CreateSolidColorBrush((D2D1_COLOR_F*)&color, (D2D1_BRUSH_PROPERTIES*)&properties, &solidColorBrush);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew SolidColorBrush(solidColorBrush);
	}

	GradientStopCollection^ RenderTarget::CreateGradientStopCollection(array<GradientStop>^ gradientStops)
	{
		int count = gradientStops->Length;
		pin_ptr<GradientStop> p = &gradientStops[0];
		D2D1_GRADIENT_STOP* gs = (D2D1_GRADIENT_STOP*)p;
		ID2D1GradientStopCollection *gradientStopCollection;
		HRESULT hr = GetNative()->CreateGradientStopCollection(gs, count, &gradientStopCollection);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew GradientStopCollection(gradientStopCollection);
	}

	GradientStopCollection^ RenderTarget::CreateGradientStopCollection(array<GradientStop>^ gradientStops, Gamma colorInterpolationGamma, ExtendMode extendMode)
	{
		int count = gradientStops->Length;
		pin_ptr<GradientStop> p = &gradientStops[0];
		D2D1_GRADIENT_STOP* gs = (D2D1_GRADIENT_STOP*)p;
		ID2D1GradientStopCollection *gradientStopCollection;
		HRESULT hr = GetNative()->CreateGradientStopCollection(gs, count, (D2D1_GAMMA)colorInterpolationGamma, (D2D1_EXTEND_MODE)extendMode, &gradientStopCollection);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew GradientStopCollection(gradientStopCollection);
	}

	LinearGradientBrush^ RenderTarget::CreateLinearGradientBrush(LinearGradientBrushProperties linearGradientBrushProperties,
			BrushProperties brushProperties,
			GradientStopCollection^ gradientStopCollection)
	{
		ID2D1LinearGradientBrush *brush;
		HRESULT hr = GetNative()->CreateLinearGradientBrush(
			(D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES *)&linearGradientBrushProperties,
			(D2D1_BRUSH_PROPERTIES *)&brushProperties,
			gradientStopCollection->GetNative(),
			&brush);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew LinearGradientBrush(brush);
	}

	RadialGradientBrush^ RenderTarget::CreateRadialGradientBrush(
			RadialGradientBrushProperties radialGradientBrushProperties,
			BrushProperties brushProperties,
			GradientStopCollection^ gradientStopCollection)
	{
		ID2D1RadialGradientBrush *brush;
		HRESULT hr = GetNative()->CreateRadialGradientBrush(
			(D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES *)&radialGradientBrushProperties,
			(D2D1_BRUSH_PROPERTIES *)&brushProperties,
			gradientStopCollection->GetNative(),
			&brush);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew RadialGradientBrush(brush);
	}

	BitmapBrush^ RenderTarget::CreateBitmapBrush(Bitmap^ bitmap, BitmapBrushProperties bitmapBrushProperties, BrushProperties brushProperties)
	{
		ID2D1BitmapBrush* brush;
		HRESULT hr = GetNative()->CreateBitmapBrush(
			bitmap->GetNative(),
			(D2D1_BITMAP_BRUSH_PROPERTIES *)&bitmapBrushProperties,
			(D2D1_BRUSH_PROPERTIES *)&brushProperties,
			&brush);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew BitmapBrush(brush);
	}

	BitmapBrush^ RenderTarget::CreateGridPatternBrush(SizeF cellSize, Color gridColor)
	{
		ID2D1BitmapBrush* bitmapBrush = NULL;
		ID2D1RenderTarget* renderTarget = GetNative();
		ID2D1BitmapRenderTarget* compatibleRenderTarget;
		HRESULT hr = renderTarget->CreateCompatibleRenderTarget(*(D2D1_SIZE_F*)&cellSize, &compatibleRenderTarget);
		if(SUCCEEDED(hr))
		{
			ID2D1SolidColorBrush* gridBrush;
			hr = compatibleRenderTarget->CreateSolidColorBrush(*(D2D1::ColorF*)&gridColor, &gridBrush);
			if(SUCCEEDED(hr))
			{
				compatibleRenderTarget->BeginDraw();
				compatibleRenderTarget->FillRectangle(D2D1::RectF(0, 0, cellSize.Width, 1), gridBrush);
				compatibleRenderTarget->FillRectangle(D2D1::RectF(0, 0, 1, cellSize.Height), gridBrush);
				hr = compatibleRenderTarget->EndDraw();
				if(SUCCEEDED(hr))
				{
					ID2D1Bitmap* bitmap;
					hr = compatibleRenderTarget->GetBitmap(&bitmap);
					if(SUCCEEDED(hr))
					{
						BitmapBrushProperties bbp = BitmapBrushProperties(ExtendMode::Wrap, ExtendMode::Wrap, BitmapInterpolationMode::Linear);
						hr = renderTarget->CreateBitmapBrush(
							bitmap, 
							D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP), 
							&bitmapBrush);
						bitmap->Release();
					}
				}
				gridBrush->Release();
			}
			compatibleRenderTarget->Release();
		}
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew BitmapBrush(bitmapBrush);
	}

	Layer^ RenderTarget::CreateLayer()
	{
		ID2D1Layer* layer;
		HRESULT hr = GetNative()->CreateLayer(&layer);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew Layer(layer);
	}

	Layer^ RenderTarget::CreateLayer(SizeF size)
	{
		ID2D1Layer* layer;
		HRESULT hr = GetNative()->CreateLayer(*(D2D1_SIZE_F*)&size, &layer);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew Layer(layer);
	}

	void RenderTarget::PushLayer(LayerParameters^ layerParameters, Layer^ layer)
	{
		if(layerParameters == nullptr)
			throw gcnew ArgumentNullException("layerParameters");
		if(layer == nullptr)
			throw gcnew ArgumentNullException("layer");
		D2D1_LAYER_PARAMETERS lp;
		RectF bounds = layerParameters->Bounds;
		lp.contentBounds = *(D2D1_RECT_F*)&bounds;
		lp.geometricMask = layerParameters->Mask == nullptr ? NULL : layerParameters->Mask->GetNative();
		lp.maskAntialiasMode = (D2D1_ANTIALIAS_MODE)layerParameters->MaskAntialiasMode;
		Matrix3x2 matrix = layerParameters->MaskTransform;
		lp.maskTransform = *(D2D1_MATRIX_3X2_F*)&matrix;
		lp.opacity = layerParameters->Opacity;
		lp.opacityBrush = layerParameters->OpacityBrush == nullptr ? NULL : layerParameters->OpacityBrush->GetNative();
		lp.layerOptions = (D2D1_LAYER_OPTIONS)layerParameters->LayerOptions;

		GetNative()->PushLayer(&lp, layer->GetNative());
	}

	void RenderTarget::FillMesh(Brush^ brush, Mesh^ mesh)
	{
		GetNative()->FillMesh(mesh->GetNative(), brush->GetNative());
	}

	void RenderTarget::FillGeometry(Brush^ brush, Brush^ opacityBrush, Geometry^ geometry)
	{
		GetNative()->FillGeometry(geometry->GetNative(), brush->GetNative(), opacityBrush->GetNative());
	}

	void RenderTarget::FillGeometry(Brush^ brush, Geometry^ geometry)
	{
		GetNative()->FillGeometry(geometry->GetNative(), brush->GetNative(), NULL);
	}

	void RenderTarget::DrawGeometry(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, Geometry^ geometry)
	{
		GetNative()->DrawGeometry(geometry->GetNative(), brush->GetNative(), strokeWidth, style->GetNative());
	}

	void RenderTarget::DrawGeometry(Brush^ brush, FLOAT strokeWidth, Geometry^ geometry)
	{
		GetNative()->DrawGeometry(geometry->GetNative(), brush->GetNative(), strokeWidth, NULL);
	}

	void RenderTarget::DrawText(String^ string, TextFormat^ textFormat, RectF layoutRect, Brush^ brush, DrawTextOptions options, MeasuringMode measuringMode)
	{
		pin_ptr<const Char> pString = string == nullptr ? nullptr : PtrToStringChars(string);

		GetNative()->DrawText(
			pString,
			string == nullptr ? 0 : string->Length,
			textFormat->GetNative(),
			(D2D1_RECT_F *)(&layoutRect),
			brush->GetNative(),
			(D2D1_DRAW_TEXT_OPTIONS)options,
			(DWRITE_MEASURING_MODE)measuringMode);
	}

	void RenderTarget::DrawTextLayout(PointF origin, TextLayout^ textLayout, Brush^ defaultForegroundBrush, DrawTextOptions options)
	{
		GetNative()->DrawTextLayout(
			*(D2D1_POINT_2F*)&origin,
			textLayout->GetNative(),
			defaultForegroundBrush->GetNative(),
			(D2D1_DRAW_TEXT_OPTIONS)options);
	}

	void RenderTarget::DrawGlyphRun(PointF baselineOrigin, GlyphRun^ glyphRun, Brush^ foregroundBrush, MeasuringMode measuringMode)
	{
		DWRITE_GLYPH_RUN gr = {0};
		glyphRun->CopyTo(&gr);
		GetNative()->DrawGlyphRun(
			*(D2D1_POINT_2F*)&baselineOrigin,
			&gr,
			foregroundBrush->GetNative(),
			(DWRITE_MEASURING_MODE)measuringMode);
	}

	void RenderTarget::DrawBitmap(Bitmap^ bitmap, RectF dstRect, Single opacity, BitmapInterpolationMode interpolationMode, RectF srcRect)
	{
		GetNative()->DrawBitmap(
			bitmap->GetNative(), 
			(D2D1_RECT_F *)&dstRect, 
			opacity,
			(D2D1_BITMAP_INTERPOLATION_MODE)interpolationMode,
			(D2D1_RECT_F *)&srcRect);
	}

	void RenderTarget::DrawBitmap(Bitmap^ bitmap, RectF dstRect, Single opacity, BitmapInterpolationMode interpolationMode)
	{
		GetNative()->DrawBitmap(
			bitmap->GetNative(), 
			(D2D1_RECT_F *)&dstRect, 
			opacity,
			(D2D1_BITMAP_INTERPOLATION_MODE)interpolationMode,
			NULL);
	}
}}}