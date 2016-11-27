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

namespace Managed {
	namespace Graphics {
		namespace Direct2D
		{

			void RenderTarget::FillRect(Brush^ brush, RectF rect)
			{
				GetNative<ID2D1RenderTarget>()->FillRectangle(reinterpret_cast<D2D1_RECT_F*>(&rect), brush->GetNative<ID2D1Brush>());
			}

			void RenderTarget::DrawRect(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, RectF rect)
			{
				GetNative<ID2D1RenderTarget>()->DrawRectangle((D2D1_RECT_F*) &rect, brush->GetNative<ID2D1Brush>(), strokeWidth, style->GetNative<ID2D1StrokeStyle>());
			}

			void RenderTarget::DrawRect(Brush^ brush, FLOAT strokeWidth, RectF rect)
			{
				GetNative<ID2D1RenderTarget>()->DrawRectangle((D2D1_RECT_F*) &rect, brush->GetNative<ID2D1Brush>(), strokeWidth, NULL);
			}

			void RenderTarget::FillRoundedRect(Brush^ brush, RoundedRect rect)
			{
				GetNative<ID2D1RenderTarget>()->FillRoundedRectangle(reinterpret_cast<D2D1_ROUNDED_RECT*>(&rect), brush->GetNative<ID2D1Brush>());
			}

			void RenderTarget::DrawRoundedRect(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, RoundedRect rect)
			{
				GetNative<ID2D1RenderTarget>()->DrawRoundedRectangle((D2D1_ROUNDED_RECT*) &rect, brush->GetNative<ID2D1Brush>(), strokeWidth, style->GetNative<ID2D1StrokeStyle>());
			}

			void RenderTarget::DrawRoundedRect(Brush^ brush, FLOAT strokeWidth, RoundedRect rect)
			{
				GetNative<ID2D1RenderTarget>()->DrawRoundedRectangle((D2D1_ROUNDED_RECT*) &rect, brush->GetNative<ID2D1Brush>(), strokeWidth, NULL);
			}

			void RenderTarget::FillEllipse(Brush^ brush, Ellipse ellipse)
			{
				GetNative<ID2D1RenderTarget>()->FillEllipse(reinterpret_cast<D2D1_ELLIPSE*>(&ellipse), brush->GetNative<ID2D1Brush>());
			}

			void RenderTarget::DrawEllipse(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, Ellipse ellipse)
			{
				GetNative<ID2D1RenderTarget>()->DrawEllipse((D2D1_ELLIPSE*) &ellipse, brush->GetNative<ID2D1Brush>(), strokeWidth, style->GetNative<ID2D1StrokeStyle>());
			}

			void RenderTarget::DrawEllipse(Brush^ brush, FLOAT strokeWidth, Ellipse ellipse)
			{
				GetNative<ID2D1RenderTarget>()->DrawEllipse((D2D1_ELLIPSE*) &ellipse, brush->GetNative<ID2D1Brush>(), strokeWidth, NULL);
			}

			void RenderTarget::DrawLine(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, PointF p0, PointF p1)
			{
				GetNative<ID2D1RenderTarget>()->DrawLine(*(D2D1_POINT_2F*) &p0, *(D2D1_POINT_2F*) &p1, brush->GetNative<ID2D1Brush>(), strokeWidth, style->GetNative<ID2D1StrokeStyle>());
			}

			void RenderTarget::DrawLine(Brush^ brush, FLOAT strokeWidth, PointF p0, PointF p1)
			{
				GetNative<ID2D1RenderTarget>()->DrawLine(*(D2D1_POINT_2F*) &p0, *(D2D1_POINT_2F*) &p1, brush->GetNative<ID2D1Brush>(), strokeWidth, NULL);
			}

			Bitmap^ RenderTarget::CreateBitmap(SizeU size, IntPtr srcData, UInt32 pitch, BitmapProperties^ bitmapProperties)
			{
				D2D1_BITMAP_PROPERTIES properties = D2D1::BitmapProperties(
					*(D2D1_PIXEL_FORMAT*) &bitmapProperties->Format,
					bitmapProperties->DpiX,
					bitmapProperties->DpiY
					);
				ID2D1Bitmap *bitmap;
				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateBitmap(
					*(D2D1_SIZE_U*) &size,
					srcData.ToPointer(),
					pitch,
					&properties,
					&bitmap));

				return gcnew Bitmap(bitmap);
			}

			Bitmap^ RenderTarget::CreateBitmap(SizeU size, array<Byte>^ srcData, UInt32 pitch, BitmapProperties^ bitmapProperties)
			{
				pin_ptr<Byte> p = &srcData[0];

				D2D1_BITMAP_PROPERTIES properties = D2D1::BitmapProperties(
					*(D2D1_PIXEL_FORMAT*) &bitmapProperties->Format,
					bitmapProperties->DpiX,
					bitmapProperties->DpiY
					);
				ID2D1Bitmap *bitmap;

				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateBitmap(
					*(D2D1_SIZE_U*) &size,
					p,
					pitch,
					&properties,
					&bitmap));

				return gcnew Bitmap(bitmap);
			}

			Bitmap^ RenderTarget::CreateBitmap(WicBitmapSource^ source, BitmapProperties^ bitmapProperties)
			{
				D2D1_BITMAP_PROPERTIES properties = D2D1::BitmapProperties(
					*(D2D1_PIXEL_FORMAT*) &bitmapProperties->Format,
					bitmapProperties->DpiX,
					bitmapProperties->DpiY
					);
				ID2D1Bitmap *bitmap;

				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateBitmapFromWicBitmap(
					source->GetNative<IWICBitmapSource>(),
					&properties,
					&bitmap));

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
									BitmapProperties^ bitmapProperties = gcnew BitmapProperties();
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
				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateCompatibleRenderTarget(&bitmapRenderTarget));
				return gcnew BitmapRenderTarget(bitmapRenderTarget);
			}

			BitmapRenderTarget^ RenderTarget::CreateCompatibleRenderTarget(SizeF desiredSize)
			{
				ID2D1BitmapRenderTarget *bitmapRenderTarget;
				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateCompatibleRenderTarget(*(D2D1_SIZE_F*) &desiredSize, &bitmapRenderTarget));
				return gcnew BitmapRenderTarget(bitmapRenderTarget);
			}

			SolidColorBrush^ RenderTarget::CreateSolidColorBrush(Color color, BrushProperties properties)
			{
				ID2D1SolidColorBrush *solidColorBrush;
				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateSolidColorBrush((D2D1_COLOR_F*) &color, (D2D1_BRUSH_PROPERTIES*) &properties, &solidColorBrush));
				return gcnew SolidColorBrush(solidColorBrush);
			}

			GradientStopCollection^ RenderTarget::CreateGradientStopCollection(array<GradientStop>^ gradientStops)
			{
				int count = gradientStops->Length;
				pin_ptr<GradientStop> p = &gradientStops[0];
				D2D1_GRADIENT_STOP* gs = (D2D1_GRADIENT_STOP*) p;
				ID2D1GradientStopCollection *gradientStopCollection;
				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateGradientStopCollection(gs, count, &gradientStopCollection));
				return gcnew GradientStopCollection(gradientStopCollection);
			}

			GradientStopCollection^ RenderTarget::CreateGradientStopCollection(array<GradientStop>^ gradientStops, Gamma colorInterpolationGamma, ExtendMode extendMode)
			{
				int count = gradientStops->Length;
				
				pin_ptr<GradientStop> p = &gradientStops[0];
				
				D2D1_GRADIENT_STOP* gs = (D2D1_GRADIENT_STOP*) p;
				
				ID2D1GradientStopCollection *gradientStopCollection;
				
				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateGradientStopCollection(
					gs, 
					count, 
					(D2D1_GAMMA) colorInterpolationGamma, 
					(D2D1_EXTEND_MODE) extendMode, 
					&gradientStopCollection));

				return gcnew GradientStopCollection(gradientStopCollection);
			}

			LinearGradientBrush^ RenderTarget::CreateLinearGradientBrush(LinearGradientBrushProperties linearGradientBrushProperties,
				BrushProperties brushProperties,
				GradientStopCollection^ gradientStopCollection)
			{
				ID2D1LinearGradientBrush *brush;

				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateLinearGradientBrush(
					(D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES *) &linearGradientBrushProperties,
					(D2D1_BRUSH_PROPERTIES *) &brushProperties,
					gradientStopCollection->GetNative<ID2D1GradientStopCollection>(),
					&brush));

				return gcnew LinearGradientBrush(brush);
			}

			RadialGradientBrush^ RenderTarget::CreateRadialGradientBrush(
				RadialGradientBrushProperties radialGradientBrushProperties,
				BrushProperties brushProperties,
				GradientStopCollection^ gradientStopCollection)
			{
				ID2D1RadialGradientBrush *brush;

				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateRadialGradientBrush(
					(D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES *) &radialGradientBrushProperties,
					(D2D1_BRUSH_PROPERTIES *) &brushProperties,
					gradientStopCollection->GetNative<ID2D1GradientStopCollection>(),
					&brush));

				return gcnew RadialGradientBrush(brush);
			}

			BitmapBrush^ RenderTarget::CreateBitmapBrush(Bitmap^ bitmap, BitmapBrushProperties bitmapBrushProperties, BrushProperties brushProperties)
			{
				ID2D1BitmapBrush* brush;

				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateBitmapBrush(
					bitmap->GetNative<ID2D1Bitmap>(),
					(D2D1_BITMAP_BRUSH_PROPERTIES *) &bitmapBrushProperties,
					(D2D1_BRUSH_PROPERTIES *) &brushProperties,
					&brush));

				return gcnew BitmapBrush(brush);
			}

			BitmapBrush^ RenderTarget::CreateGridPatternBrush(SizeF cellSize, Color gridColor)
			{
				ID2D1RenderTarget* renderTarget = GetNative<ID2D1RenderTarget>();
				ID2D1BitmapBrush* bitmapBrush;
				ID2D1BitmapRenderTarget* compatibleRenderTarget;

				HRESULT hr = renderTarget->CreateCompatibleRenderTarget(*(D2D1_SIZE_F*) &cellSize, &compatibleRenderTarget);
				if (SUCCEEDED(hr))
				{
					ID2D1SolidColorBrush* gridBrush;
					hr = compatibleRenderTarget->CreateSolidColorBrush(*(D2D1::ColorF*)&gridColor, &gridBrush);
					if (SUCCEEDED(hr))
					{
						compatibleRenderTarget->BeginDraw();
						compatibleRenderTarget->FillRectangle(D2D1::RectF(0, 0, cellSize.Width, 1), gridBrush);
						compatibleRenderTarget->FillRectangle(D2D1::RectF(0, 0, 1, cellSize.Height), gridBrush);
						hr = compatibleRenderTarget->EndDraw();
						if (SUCCEEDED(hr))
						{
							ID2D1Bitmap* bitmap;
							hr = compatibleRenderTarget->GetBitmap(&bitmap);
							if (SUCCEEDED(hr))
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

				ComUtils::CheckResult(hr);

				return gcnew BitmapBrush(bitmapBrush);
			}

			Layer^ RenderTarget::CreateLayer()
			{
				ID2D1Layer* layer;
				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateLayer(&layer));
				return gcnew Layer(layer);
			}

			Layer^ RenderTarget::CreateLayer(SizeF size)
			{
				ID2D1Layer* layer;
				ComUtils::CheckResult(GetNative<ID2D1RenderTarget>()->CreateLayer(*(D2D1_SIZE_F*) &size, &layer));
				return gcnew Layer(layer);
			}

			void RenderTarget::PushLayer(LayerParameters^ layerParameters, Layer^ layer)
			{
				if (layerParameters == nullptr)
					throw gcnew ArgumentNullException("layerParameters");
				if (layer == nullptr)
					throw gcnew ArgumentNullException("layer");
				D2D1_LAYER_PARAMETERS lp;
				RectF bounds = layerParameters->Bounds;
				lp.contentBounds = *(D2D1_RECT_F*) &bounds;
				lp.geometricMask = layerParameters->Mask == nullptr ? NULL : layerParameters->Mask->GetNative<ID2D1Geometry>();
				lp.maskAntialiasMode = (D2D1_ANTIALIAS_MODE) layerParameters->MaskAntialiasMode;
				Matrix3x2 matrix = layerParameters->MaskTransform;
				lp.maskTransform = *(D2D1_MATRIX_3X2_F*) &matrix;
				lp.opacity = layerParameters->Opacity;
				lp.opacityBrush = layerParameters->OpacityBrush == nullptr ? NULL : layerParameters->OpacityBrush->GetNative<ID2D1Brush>();
				lp.layerOptions = (D2D1_LAYER_OPTIONS) layerParameters->LayerOptions;

				GetNative<ID2D1RenderTarget>()->PushLayer(&lp, layer->GetNative<ID2D1Layer>());
			}

			void RenderTarget::FillMesh(Brush^ brush, Mesh^ mesh)
			{
				GetNative<ID2D1RenderTarget>()->FillMesh(
					mesh->GetNative<ID2D1Mesh>(),
					brush->GetNative<ID2D1Brush>());
			}

			void RenderTarget::FillGeometry(Brush^ brush, Brush^ opacityBrush, Geometry^ geometry)
			{
				GetNative<ID2D1RenderTarget>()->FillGeometry(
					geometry->GetNative<ID2D1Geometry>(),
					brush->GetNative<ID2D1Brush>(),
					opacityBrush->GetNative<ID2D1Brush>());
			}

			void RenderTarget::FillGeometry(Brush^ brush, Geometry^ geometry)
			{
				GetNative<ID2D1RenderTarget>()->FillGeometry(
					geometry->GetNative<ID2D1Geometry>(),
					brush->GetNative<ID2D1Brush>(),
					NULL);
			}

			void RenderTarget::DrawGeometry(Brush^ brush, FLOAT strokeWidth, StrokeStyle^ style, Geometry^ geometry)
			{
				GetNative<ID2D1RenderTarget>()->DrawGeometry(
					geometry->GetNative<ID2D1Geometry>(),
					brush->GetNative<ID2D1Brush>(),
					strokeWidth,
					style->GetNative<ID2D1StrokeStyle>());
			}

			void RenderTarget::DrawGeometry(Brush^ brush, FLOAT strokeWidth, Geometry^ geometry)
			{
				GetNative<ID2D1RenderTarget>()->DrawGeometry(
					geometry->GetNative<ID2D1Geometry>(),
					brush->GetNative<ID2D1Brush>(),
					strokeWidth,
					NULL);
			}

			void RenderTarget::DrawText(String^ string, TextFormat^ textFormat, RectF layoutRect, Brush^ brush, DrawTextOptions options, MeasuringMode measuringMode)
			{
				pin_ptr<const Char> pString = string == nullptr ? nullptr : PtrToStringChars(string);

				GetNative<ID2D1RenderTarget>()->DrawText(
					pString,
					string == nullptr ? 0 : string->Length,
					textFormat->GetNative<IDWriteTextFormat>(),
					(D2D1_RECT_F *) (&layoutRect),
					brush->GetNative<ID2D1Brush>(),
					(D2D1_DRAW_TEXT_OPTIONS) options,
					(DWRITE_MEASURING_MODE) measuringMode);
			}

			void RenderTarget::DrawTextLayout(PointF origin, TextLayout^ textLayout, Brush^ defaultForegroundBrush, DrawTextOptions options)
			{
				GetNative<ID2D1RenderTarget>()->DrawTextLayout(
					*(D2D1_POINT_2F*) &origin,
					textLayout->GetNative<IDWriteTextLayout>(),
					defaultForegroundBrush->GetNative<ID2D1Brush>(),
					(D2D1_DRAW_TEXT_OPTIONS) options);
			}

			void RenderTarget::DrawGlyphRun(PointF baselineOrigin, GlyphRun^ glyphRun, Brush^ foregroundBrush, MeasuringMode measuringMode)
			{
				DWRITE_GLYPH_RUN gr = { 0 };
				glyphRun->CopyTo(&gr);
				GetNative<ID2D1RenderTarget>()->DrawGlyphRun(
					*(D2D1_POINT_2F*) &baselineOrigin,
					&gr,
					foregroundBrush->GetNative<ID2D1Brush>(),
					(DWRITE_MEASURING_MODE) measuringMode);
			}

			void RenderTarget::DrawBitmap(Bitmap^ bitmap, RectF dstRect, Single opacity, BitmapInterpolationMode interpolationMode, RectF srcRect)
			{
				GetNative<ID2D1RenderTarget>()->DrawBitmap(
					bitmap->GetNative<ID2D1Bitmap>(),
					(D2D1_RECT_F *) &dstRect,
					opacity,
					(D2D1_BITMAP_INTERPOLATION_MODE) interpolationMode,
					(D2D1_RECT_F *) &srcRect);
			}

			void RenderTarget::DrawBitmap(Bitmap^ bitmap, RectF dstRect, Single opacity, BitmapInterpolationMode interpolationMode)
			{
				GetNative<ID2D1RenderTarget>()->DrawBitmap(
					bitmap->GetNative<ID2D1Bitmap>(),
					(D2D1_RECT_F *) &dstRect,
					opacity,
					(D2D1_BITMAP_INTERPOLATION_MODE) interpolationMode,
					NULL);
			}
		}
	}
}