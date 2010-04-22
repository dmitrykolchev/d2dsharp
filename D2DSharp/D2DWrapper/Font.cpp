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
		GetNative()->CreateFontFace(&fontFace));

	return gcnew FontFace(fontFace);
}

LocalizedStrings^ Font::FaceNames::get()
{
	IDWriteLocalizedStrings* names;

	ComUtils::CheckResult(
		GetNative()->GetFaceNames(&names));
	
	return gcnew LocalizedStrings(names);
}

FontFamily^ Font::Family::get()
{
	IDWriteFontFamily* fontFamily;

	ComUtils::CheckResult(
		GetNative()->GetFontFamily(&fontFamily));

	return gcnew FontFamily(fontFamily);
}

LocalizedStrings^ Font::GetInformationalStrings(InformationalStringId id, [Out]Boolean% exists)
{
	IDWriteLocalizedStrings* strings;
	BOOL bExists;

	ComUtils::CheckResult(
		GetNative()->GetInformationalStrings(
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
		GetNative()->GetInformationalStrings(
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
	GetNative()->GetMetrics((DWRITE_FONT_METRICS*)&metrics);
	return metrics;
}

FontSimulations Font::Simulations::get()
{
	return (FontSimulations)GetNative()->GetSimulations();
}

FontStretch Font::Stretch::get()
{
	return (FontStretch)GetNative()->GetStretch();
}

FontStyle Font::Style::get()
{
	return (FontStyle)GetNative()->GetStyle();
}

FontWeight Font::Weight::get()
{
	return (FontWeight)GetNative()->GetWeight();
}

Boolean Font::HasCharacter(UInt32 unicodeValue)
{
	BOOL exists;
	ComUtils::CheckResult(GetNative()->HasCharacter(unicodeValue, &exists));
	return exists != 0;
}

Boolean Font::IsSymbolFont::get()
{
	return GetNative()->IsSymbolFont() != 0;
}
