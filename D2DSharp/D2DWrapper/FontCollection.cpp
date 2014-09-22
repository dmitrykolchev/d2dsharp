/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;


FontFamily^ FontCollection::default::get(int index)
{
	IDWriteFontFamily *fontFamily;
	ComUtils::CheckResult(GetNative<IDWriteFontCollection>()->GetFontFamily(index, &fontFamily));
	return gcnew FontFamily(fontFamily);
}

Int32 FontCollection::Count::get()
{
	return (Int32) GetNative<IDWriteFontCollection>()->GetFontFamilyCount();
}

Int32 FontCollection::FindFamilyName(String^ familyName)
{
	pin_ptr<const wchar_t> pFamilyName = PtrToStringChars(familyName);
	UINT32 index;
	BOOL exists;
	ComUtils::CheckResult(GetNative<IDWriteFontCollection>()->FindFamilyName(pFamilyName, &index, &exists));
	if(!exists)
		return -1;
	return (Int32)index;
}

Font^ FontCollection::GetFontFromFontFace(FontFace^ fontFace)
{
	IDWriteFont* font;
	ComUtils::CheckResult(
		GetNative<IDWriteFontCollection>()->GetFontFromFontFace(
			fontFace->GetNative<IDWriteFontFace>(),
			&font));
	return gcnew Font(font);
}
