/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "DWCommon.h"
#include "DirectWriteFactory.h"
#include "TextFormat.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace DirectWrite 
{
	void DirectWriteFactory::GetDpiScale([Out]Single% dpiScaleX, [Out]Single% dpiScaleY)
	{
		HDC screen = GetDC(0);
		dpiScaleX = GetDeviceCaps(screen, LOGPIXELSX) / 96.0f;
		dpiScaleY = GetDeviceCaps(screen, LOGPIXELSY) / 96.0f;
		ReleaseDC(0, screen);
	}

	DirectWriteFactory^ DirectWriteFactory::Create(DirectWriteFactoryType factoryType)
	{
		IDWriteFactory *writeFactory;

		ComUtils::CheckResult(DWriteCreateFactory(
			(DWRITE_FACTORY_TYPE)factoryType, 
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&writeFactory)));

		return gcnew DirectWriteFactory(writeFactory);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(
		String^ fontFamilyName, 
		Single fontSize)
	{
		return CreateTextFormat(fontFamilyName, fontSize, FontWeight::Normal, FontStyle::Normal, FontStretch::Normal, nullptr, System::Globalization::CultureInfo::CurrentUICulture);
	}
	TextFormat^ DirectWriteFactory::CreateTextFormat(
		String^ fontFamilyName,
		Single fontSize,
		FontWeight fontWeight)
	{
		return CreateTextFormat(fontFamilyName, fontSize, fontWeight, FontStyle::Normal, FontStretch::Normal, nullptr, System::Globalization::CultureInfo::CurrentUICulture);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(
		String^ fontFamilyName,
		Single fontSize,
		FontWeight fontWeight,
		FontStyle fontStyle)
	{
		return CreateTextFormat(fontFamilyName, fontSize, fontWeight, fontStyle, FontStretch::Normal, nullptr, System::Globalization::CultureInfo::CurrentUICulture);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(
		String^ fontFamilyName,
		Single fontSize,
		FontWeight fontWeight,
		FontStyle fontStyle,
		FontStretch fontStretch)
	{
		return CreateTextFormat(fontFamilyName, fontSize, fontWeight, fontStyle, fontStretch, nullptr, System::Globalization::CultureInfo::CurrentUICulture);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(
		String^ fontFamilyName,
		Single fontSize,
		FontWeight fontWeight,
		FontStyle fontStyle,
		FontStretch fontStretch,
		FontCollection^ fontCollection,
		System::Globalization::CultureInfo^ culture)
	{
		if (fontFamilyName == nullptr)
			throw gcnew ArgumentNullException("fontFamilyName");

		pin_ptr<const System::Char> pFontFamily = PtrToStringChars(fontFamilyName);

		String^ localeName = culture == nullptr ? String::Empty : culture->Name;

		pin_ptr<const System::Char> pLocaleName = localeName == nullptr ? L"" : PtrToStringChars(localeName);

		IDWriteFontCollection* pFontCollection = fontCollection == nullptr ? NULL : fontCollection->GetNative<IDWriteFontCollection>();

		IDWriteTextFormat *textFormat;

		ComUtils::CheckResult(GetNative<IDWriteFactory>()->CreateTextFormat(
			pFontFamily,
			pFontCollection,
			(DWRITE_FONT_WEIGHT) fontWeight,
			(DWRITE_FONT_STYLE) fontStyle,
			(DWRITE_FONT_STRETCH) fontStretch,
			fontSize,
			pLocaleName,
			&textFormat));

		return gcnew TextFormat(textFormat);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(
		String^ fontFamilyName, 
		FontWeight fontWeight, 
		Single fontSize)
	{
		return CreateTextFormat(fontFamilyName, fontSize, fontWeight, FontStyle::Normal, FontStretch::Normal, nullptr, System::Globalization::CultureInfo::CurrentUICulture);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(
		String^ fontFamilyName, 
		FontWeight fontWeight, 
		FontStyle fontStyle, 
		Single fontSize)
	{
		return CreateTextFormat(fontFamilyName, fontSize, fontWeight, fontStyle, FontStretch::Normal, nullptr, System::Globalization::CultureInfo::CurrentUICulture);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(
		String^ fontFamilyName, 
		FontWeight fontWeight, 
		FontStyle fontStyle, 
		FontStretch fontStretch, 
		Single fontSize)
	{
		return CreateTextFormat(fontFamilyName, fontSize, fontWeight, fontStyle, fontStretch, nullptr, System::Globalization::CultureInfo::CurrentUICulture);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(
		String^ fontFamilyName, 
		FontCollection^ fontCollection, 
		FontWeight fontWeight, 
		FontStyle fontStyle, 
		FontStretch fontStretch, 
		Single fontSize, 
		System::Globalization::CultureInfo^ culture)
	{
		if(fontFamilyName == nullptr)
			throw gcnew ArgumentNullException("fontFamilyName");

		pin_ptr<const System::Char> pFontFamily = PtrToStringChars(fontFamilyName);
		
		String^ localeName = culture == nullptr ? String::Empty : culture->Name;

		pin_ptr<const System::Char> pLocaleName = localeName == nullptr ? L"" : PtrToStringChars(localeName);
		
		IDWriteFontCollection* pFontCollection = fontCollection == nullptr ? NULL : fontCollection->GetNative<IDWriteFontCollection>();
		
		IDWriteTextFormat *textFormat;

		ComUtils::CheckResult(GetNative<IDWriteFactory>()->CreateTextFormat(
			pFontFamily, 
			pFontCollection, 
			(DWRITE_FONT_WEIGHT)fontWeight, 
			(DWRITE_FONT_STYLE)fontStyle,
			(DWRITE_FONT_STRETCH)fontStretch,
			fontSize,
			pLocaleName,
			&textFormat));
		
		return gcnew TextFormat(textFormat);
	}
	
	TextLayout^ DirectWriteFactory::CreateTextLayout(String^ string, TextFormat^ textFormat, FLOAT maxWidth, FLOAT maxHeight)
	{
		pin_ptr<const System::Char> pString = PtrToStringChars(string);
		IDWriteTextLayout* textLayout;
		ComUtils::CheckResult(GetNative<IDWriteFactory>()->CreateTextLayout(
			pString,
			string->Length,
			textFormat->GetNative<IDWriteTextFormat>(),
			maxWidth,
			maxHeight,
			&textLayout));
		return gcnew TextLayout(textLayout);
	}

	Typography^ DirectWriteFactory::CreateTypography()
	{
		IDWriteTypography* value;
		ComUtils::CheckResult(GetNative<IDWriteFactory>()->CreateTypography(&value));
		return gcnew Typography(value);
	}

	FontCollection^ DirectWriteFactory::CreateCustomFontCollection(FontCollectionLoader^ collectionLoader, array<Byte>^ collectionKey)
	{
		IDWriteFontCollection* fontCollection;

		pin_ptr<Byte> pCollectionKey = &collectionKey[0];
		
		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateCustomFontCollection(
				collectionLoader->GetNative<IDWriteFontCollectionLoader>(),
				pCollectionKey,
				collectionKey->Length,
				&fontCollection));

		return gcnew FontCollection(fontCollection);
	}
		
	FontFile^ DirectWriteFactory::CreateCustomFontFileReference(array<Byte>^ fontFileReferenceKey, FontFileLoader^ fontFileLoader)
	{
		IDWriteFontFile* fontFile;
		pin_ptr<Byte> pFontFileReferenceKey = &fontFileReferenceKey[0];

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateCustomFontFileReference(
				pFontFileReferenceKey,
				fontFileReferenceKey->Length,
				fontFileLoader->GetNative<IDWriteFontFileLoader>(),
				&fontFile));

		return gcnew FontFile(fontFile);
	}
		
	RenderingParams^ DirectWriteFactory::CreateCustomRenderingParams(Single gamma, Single enchancedContrast, Single clearTypeLevel,
		PixelGeometry pixelGeometry, RenderingMode renderingMode)
	{
		IDWriteRenderingParams* renderingParams;

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateCustomRenderingParams(
				gamma,
				enchancedContrast,
				clearTypeLevel,
				(DWRITE_PIXEL_GEOMETRY)pixelGeometry,
				(DWRITE_RENDERING_MODE)renderingMode,
				&renderingParams));
		return gcnew RenderingParams(renderingParams);
	}
		
	TextLayout^ DirectWriteFactory::CreateGdiCompatibleTextLayout(String^ string, TextFormat^ textFormat, 
		Single layoutWidth, Single layoutHeight, Single pixelsPerDip, D2D::Matrix3x2 transform, 
		Boolean useGdiNatural)
	{
		IDWriteTextLayout* textLayout;

		pin_ptr<const wchar_t> pString = PtrToStringChars(string);

		DWRITE_MATRIX matrix = { 
			transform.M11, transform.M12,
			transform.M21, transform.M22,
			transform.M31, transform.M32 
		};

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateGdiCompatibleTextLayout(
				pString,
				string->Length,
				textFormat->GetNative<IDWriteTextFormat>(),
				layoutWidth,
				layoutHeight,
				pixelsPerDip,
				&matrix,
				useGdiNatural,
				&textLayout));

		return gcnew TextLayout(textLayout);
	}
		
	InlineObject^ DirectWriteFactory::CreateEllipsisTrimmingSign(TextFormat^ textFormat)
	{
		IDWriteInlineObject *inlineObject;

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateEllipsisTrimmingSign(
				textFormat->GetNative<IDWriteTextFormat>(),
				&inlineObject));

		return gcnew InlineObjectWrapper(inlineObject, false);
	}

	typedef IDWriteFontFile* PIDWriteFontFile;
		
	FontFace^ DirectWriteFactory::CreateFontFace(FontFaceType fontFaceType, array<FontFile^>^ fontFiles, UInt32 faceIndex, 
		FontSimulations fontFaceSimulationFlags)
	{
		IDWriteFontFace* fontFace;

		int count = fontFiles->Length;

		PIDWriteFontFile* pFontFiles = new PIDWriteFontFile[count];
		try
		{
			for(int index = 0; index < count; ++index)
			{
				pFontFiles[index] = fontFiles[index]->GetNative<IDWriteFontFile>();
			}

			ComUtils::CheckResult(
				GetNative<IDWriteFactory>()->CreateFontFace(
					(DWRITE_FONT_FACE_TYPE)fontFaceType,
					fontFiles->Length,
					pFontFiles,
					faceIndex,
					(DWRITE_FONT_SIMULATIONS)fontFaceSimulationFlags,
					&fontFace));

			return gcnew FontFace(fontFace);
		}
		finally
		{
			delete pFontFiles;
		}
	}
		
	FontFile^ DirectWriteFactory::CreateFontFileReference(String^ filePath, DateTime lastWriteTime)
	{
		IDWriteFontFile* fontFile;
		pin_ptr<const wchar_t> pFilePath = PtrToStringChars(filePath);
		
		__int64 ift = lastWriteTime.ToFileTime();
		::FILETIME ft = *(::FILETIME*)&ift;

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateFontFileReference(pFilePath, &ft, &fontFile));

		return gcnew FontFile(fontFile);
	}
	
	GlyphRunAnalysis^ DirectWriteFactory::CreateGlyphRunAnalysis(GlyphRun^ glyphRun, Single pixelsPerDip, 
		D2D::Matrix3x2 transform, 
		RenderingMode renderingMode, D2D::MeasuringMode measuringMode,
		Single baselineOriginX, Single baselineOriginY)
	{
		IDWriteGlyphRunAnalysis* glyphRunAnalysis;

		DWRITE_MATRIX matrix = { 
			transform.M11, transform.M12,
			transform.M21, transform.M22,
			transform.M31, transform.M32 
		};

		DWRITE_GLYPH_RUN gr;
		glyphRun->CopyTo(&gr);

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateGlyphRunAnalysis(
				&gr,
				pixelsPerDip,
				&matrix,
				(DWRITE_RENDERING_MODE)renderingMode,
				(DWRITE_MEASURING_MODE)measuringMode,
				baselineOriginX,
				baselineOriginY,
				&glyphRunAnalysis));

		return gcnew GlyphRunAnalysis(glyphRunAnalysis);
	}

	RenderingParams^ DirectWriteFactory::CreateMonitorRenderingParams(IntPtr monitor)
	{
		IDWriteRenderingParams* renderingParams;

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateMonitorRenderingParams(
				(HMONITOR)monitor.ToPointer(),
				&renderingParams));

		return gcnew RenderingParams(renderingParams);
	}

	NumberSubstitution^ DirectWriteFactory::CreateNumberSubstitution(NumberSubstitutionMethod substitutionMethod, 
		System::Globalization::CultureInfo^ culture, Boolean ignoreUserOverride)
	{
		IDWriteNumberSubstitution* numberSubstitution;
		String^ localeName = culture->Name;
		pin_ptr<const wchar_t> pLocaleName = PtrToStringChars(localeName);

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateNumberSubstitution(
				(DWRITE_NUMBER_SUBSTITUTION_METHOD)substitutionMethod,
				pLocaleName,
				ignoreUserOverride,
				&numberSubstitution));

		return gcnew NumberSubstitution(numberSubstitution);
	}

	RenderingParams^ DirectWriteFactory::CreateRenderingParams()
	{
		IDWriteRenderingParams* renderingParams;
		
		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateRenderingParams(&renderingParams));

		return gcnew RenderingParams(renderingParams);
	}

	TextAnalyzer^ DirectWriteFactory::CreateTextAnalyzer()
	{
		IDWriteTextAnalyzer* textAnalyzer;

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->CreateTextAnalyzer(&textAnalyzer));

		return gcnew TextAnalyzer(textAnalyzer);
	}

	GdiInterop^ DirectWriteFactory::GetGdiInterop()
	{
		IDWriteGdiInterop* gdiInterop;

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->GetGdiInterop(&gdiInterop));

		return gcnew GdiInterop(gdiInterop);
	}

	FontCollection^ DirectWriteFactory::GetSystemFontCollection(Boolean checkForUpdates)
	{
		IDWriteFontCollection* fontCollection;

		ComUtils::CheckResult(
			GetNative<IDWriteFactory>()->GetSystemFontCollection(&fontCollection, checkForUpdates));

		return gcnew FontCollection(fontCollection);
	}

	void DirectWriteFactory::RegisterFontCollectionLoader(FontCollectionLoader^ fontCollectionLoader)
	{
		ComUtils::CheckResult(GetNative<IDWriteFactory>()->RegisterFontCollectionLoader(fontCollectionLoader->GetNative<IDWriteFontCollectionLoader>()));
	}

	void DirectWriteFactory::RegisterFontFileLoader(FontFileLoader^ fontFileLoader)
	{
		ComUtils::CheckResult(GetNative<IDWriteFactory>()->RegisterFontFileLoader(fontFileLoader->GetNative<IDWriteFontFileLoader>()));
	}

	void DirectWriteFactory::UnregisterFontCollectionLoader(FontCollectionLoader^ fontCollectionLoader)
	{
		ComUtils::CheckResult(GetNative<IDWriteFactory>()->UnregisterFontCollectionLoader(fontCollectionLoader->GetNative<IDWriteFontCollectionLoader>()));
	}

	void DirectWriteFactory::UnregisterFontFileLoader(FontFileLoader^ fontFileLoader)
	{
		ComUtils::CheckResult(GetNative<IDWriteFactory>()->UnregisterFontFileLoader(fontFileLoader->GetNative<IDWriteFontFileLoader>()));
	}

}}}