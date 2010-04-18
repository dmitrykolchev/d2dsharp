/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#pragma comment(lib, "dwrite.lib")

#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace D2D = Managed::Graphics::Direct2D;

namespace Managed { namespace Graphics { namespace DirectWrite 
{

	ref class TextFormat;
	ref class FontCollection;
	ref class TextLayout;
	ref class Typography;
	ref class FontCollectionLoader;
	ref class FontFileLoader;
	ref class FontFile;
	ref class RenderingParams;
	ref class InlineObject;
	ref class GlyphRunAnalysis;
	ref class NumberSubstitution;
	ref class GdiInterop;
	ref class TextAnalyzer;
	ref class FontFace;

	public ref class DirectWriteFactory: ComWrapper
	{
	private:
		DirectWriteFactory(IDWriteFactory* native): 
		   ComWrapper(native)
		{
		}
	public:
		static DirectWriteFactory^ Create(DirectWriteFactoryType factoryType);

		FontCollection^ CreateCustomFontCollection(FontCollectionLoader^ collectionLoader, array<Byte>^ collectionKey);
		
		FontFile^ CreateCustomFontFileReference(array<Byte>^ fontFileReferenceKey, FontFileLoader^ fontFileLoader);
		
		RenderingParams^ CreateCustomRenderingParams(Single gamma, Single enchancedContrast, Single clearTypeLevel,
			PixelGeometry pixelGeometry, RenderingMode renderingMode);
		
		TextLayout^ CreateGdiCompatibleTextLayout(String^ string, TextFormat^ textFormat, 
			Single layoutWidth, Single layoutHeight, Single pixelsPerDip, D2D::Matrix3x2 transform, 
			Boolean useGdiNatural);
		
		InlineObject^ CreateEllipsisTrimmingSign(TextFormat^ textFormat);
		
		FontFace^ CreateFontFace(FontFaceType fontFaceType, array<FontFile^>^ fontFiles, UInt32 faceIndex, 
			FontSimulations fontFaceSimulationFlags);
		
		FontFile^ CreateFontFileReference(String^ filePath, DateTime lastWriteTime);
	
		GlyphRunAnalysis^ CreateGlyphRunAnalysis(GlyphRun^ glyphRun, Single pixelsPerDip, 
			D2D::Matrix3x2 transform, 
			RenderingMode renderingMode, D2D::MeasuringMode measuringMode,
			Single baselineOriginX, Single baselineOriginY);

		RenderingParams^ CreateMonitorRenderingParams(IntPtr monitor);

		NumberSubstitution^ CreateNumberSubstitution(NumberSubstitutionMethod substitutionMethod, 
			System::Globalization::CultureInfo^ culture, Boolean ignoreUserOverride);

		RenderingParams^ CreateRenderingParams();

		TextAnalyzer^ CreateTextAnalyzer();

		GdiInterop^ GetGdiInterop();

		FontCollection^ GetSystemFontCollection(Boolean checkForUpdates);

		void RegisterFontCollectionLoader(FontCollectionLoader^ fontCollectionLoader);

		void RegisterFontFileLoader(FontFileLoader^ fontFileLoader);

		void UnregisterFontCollectionLoader(FontCollectionLoader^ fontCollectionLoader);

		void UnregisterFontFileLoader(FontFileLoader^ fontFileLoader);

		TextFormat^ CreateTextFormat(String^ fontFamilyName, FontCollection^ fontCollection, FontWeight fontWeight, FontStyle fontStyle, FontStretch fontStretch, FLOAT fontSize, String^ localeName);
		
		TextLayout^ CreateTextLayout(String^ string, TextFormat^ textFormat, FLOAT maxWidth, FLOAT maxHeight);
		
		Typography^ CreateTypography();

		static void GetDpiScale([Out]Single% dpiScaleX, [Out]Single% dpiScaleY);
	internal:
		IDWriteFactory* GetNative() new
		{
			return (IDWriteFactory*)ComWrapper::GetNative();
		}
	};
}}}
