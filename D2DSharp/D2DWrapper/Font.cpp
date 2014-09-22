/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;


FontFace^ Font::CreateFontFace()
{
	IDWriteFontFace* fontFace;

	ComUtils::CheckResult(
		GetNative<IDWriteFont>()->CreateFontFace(&fontFace));

	return gcnew FontFace(fontFace);
}

LocalizedStrings^ Font::FaceNames::get()
{
	IDWriteLocalizedStrings* names;

	ComUtils::CheckResult(
		GetNative<IDWriteFont>()->GetFaceNames(&names));
	
	return gcnew LocalizedStrings(names);
}

FontFamily^ Font::Family::get()
{
	IDWriteFontFamily* fontFamily;

	ComUtils::CheckResult(
		GetNative<IDWriteFont>()->GetFontFamily(&fontFamily));

	return gcnew FontFamily(fontFamily);
}

LocalizedStrings^ Font::GetInformationalStrings(InformationalStringId id, [Out]Boolean% exists)
{
	IDWriteLocalizedStrings* strings;
	BOOL bExists;

	ComUtils::CheckResult(
		GetNative<IDWriteFont>()->GetInformationalStrings(
			(DWRITE_INFORMATIONAL_STRING_ID)id,
			&strings,
			&bExists));
	exists = bExists != 0;
	if(exists)
		return gcnew LocalizedStrings(strings);
	return nullptr;
}

LocalizedStrings^ Font::GetInformationalStrings(InformationalStringId id)
{
	IDWriteLocalizedStrings* strings;
	BOOL bExists;

	ComUtils::CheckResult(
		GetNative<IDWriteFont>()->GetInformationalStrings(
			(DWRITE_INFORMATIONAL_STRING_ID)id,
			&strings,
			&bExists));
	if(bExists)
		return gcnew LocalizedStrings(strings);
	return nullptr;
}


FontMetrics Font::Metrics::get()
{
	FontMetrics metrics;
	GetNative<IDWriteFont>()->GetMetrics((DWRITE_FONT_METRICS*) &metrics);
	return metrics;
}

FontSimulations Font::Simulations::get()
{
	return (FontSimulations) GetNative<IDWriteFont>()->GetSimulations();
}

FontStretch Font::Stretch::get()
{
	return (FontStretch) GetNative<IDWriteFont>()->GetStretch();
}

FontStyle Font::Style::get()
{
	return (FontStyle) GetNative<IDWriteFont>()->GetStyle();
}

FontWeight Font::Weight::get()
{
	return (FontWeight) GetNative<IDWriteFont>()->GetWeight();
}

Boolean Font::HasCharacter(UInt32 unicodeValue)
{
	BOOL exists;
	ComUtils::CheckResult(GetNative<IDWriteFont>()->HasCharacter(unicodeValue, &exists));
	return exists != 0;
}

Boolean Font::IsSymbolFont::get()
{
	return GetNative<IDWriteFont>()->IsSymbolFont() != 0;
}
