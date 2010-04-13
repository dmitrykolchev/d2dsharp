// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vcclr.h>
#include <Wincodec.h>

#include "ComWrapper.h"

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

#include "WicCommon.h"
#include "WicComponentInfo.h"
#include "WicPixelFormat.h"
#include "WicImagingFactory.h"
#include "WicPalette.h"
#include "WicBitmapSource.h"
#include "WicBitmap.h"
#include "WicBitmapDecoder.h"
#include "WicBitmapFrameDecode.h"