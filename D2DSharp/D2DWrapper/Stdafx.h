/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vcclr.h>

#include "ComUtils.h"
#include "ComWrapper.h"
#include "StreamWrapper.h"
#include "D2DCommon.h"
#include "Colors.h"
#include "Direct2DFactory.h"
#include "Brush.h"
#include "SolidColorBrush.h"
#include "GradientStopCollection.h"
#include "LinearGradientBrush.h"
#include "RadialGradientBrush.h"
#include "RenderTarget.h"
#include "WindowRenderTarget.h"
#include "StrokeStyle.h"
#include "Geometry.h"
#include "EllipseGeometry.h"
#include "RectangleGeometry.h"
#include "RoundedRectangleGeometry.h"
#include "TransformedGeometry.h"
#include "PathGeometry.h"
#include "GeometryGroup.h"
#include "SimplifiedGeometrySink.h"
#include "GeometrySink.h"
#include "Layer.h"
#include "LayerParameters.h"
#include "TessellationSink.h"
#include "Mesh.h"
#include "Bitmap.h"
#include "BitmapBrush.h"
#include "BitmapRenderTarget.h"
#include "DCRenderTarget.h"

//
// DirectWrite headers
//
#include "DWCommon.h"
#include "DirectWriteFactory.h"
#include "FontCollection.h"
#include "TextFormat.h"
#include "TextLayout.h"
#include "CustomTextRenderer.h"
#include "TextRenderer.h"
#include "InlineObject.h"
#include "Typography.h"
#include "GlyphRun.h"
#include "GlyphRunAnalysis.h"
#include "FontFace.h"
#include "CustomTextRenderer.h"
#include "FontCollectionLoader.h"
#include "FontFileLoader.h"
#include "FontFile.h"
#include "FontFileStream.h"
#include "RenderingParams.h"
#include "NumberSubstitution.h"
#include "TextAnalyzer.h"
#include "GdiInterop.h"
#include "ClientDrawingEffect.h"
#include "TextAnalysisSource.h"
#include "FontFamily.h"
#include "Font.h"
#include "LocalizedStrings.h"
#include "FontList.h"

#include "WicCommon.h"
#include "WicComponentInfo.h"
#include "WicPixelFormat.h"
#include "WicImagingFactory.h"
#include "WicPalette.h"
#include "WicBitmapSource.h"
#include "WicBitmap.h"
#include "WicBitmapDecoder.h"
#include "WicBitmapFrameDecode.h"
#include "WicBitmapEncoder.h"
#include "WicBitmapEncoderInfo.h"
#include "WicBitmapCodecInfo.h"
#include "WicBitmapFrameEncode.h"
#include "WicStream.h"
#include "WicBitmapLock.h"
#include "WicGuids.h"
#include "WicColorContext.h"
#include "WicMetadataQueryReader.h"
#include "WicMetadataQueryWriter.h"
