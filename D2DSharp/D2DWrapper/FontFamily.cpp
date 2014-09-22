/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;


LocalizedStrings^ FontFamily::FamilyNames::get()
{
	IDWriteLocalizedStrings* names;

	ComUtils::CheckResult(
		GetNative<IDWriteFontFamily>()->GetFamilyNames(
			&names));
	return gcnew LocalizedStrings(names);
}

Font^ FontFamily::GetFirstMatchingFont(FontWeight weight, FontStretch stretch, FontStyle style)
{
	IDWriteFont* font;

	ComUtils::CheckResult(
		GetNative<IDWriteFontFamily>()->GetFirstMatchingFont(
			(DWRITE_FONT_WEIGHT)weight,
			(DWRITE_FONT_STRETCH)stretch,
			(DWRITE_FONT_STYLE)style,
			&font));

	return gcnew Font(font);
}

FontList^ FontFamily::GetMatchingFonts(FontWeight weight, FontStretch stretch, FontStyle style)
{
	IDWriteFontList* fonts;

	ComUtils::CheckResult(
		GetNative<IDWriteFontFamily>()->GetMatchingFonts(
			(DWRITE_FONT_WEIGHT)weight,
			(DWRITE_FONT_STRETCH)stretch,
			(DWRITE_FONT_STYLE)style,
			&fonts));

	return gcnew FontList(fonts);
}
