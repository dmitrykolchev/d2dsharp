/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"


using namespace Managed::Graphics::DirectWrite;

Int32 FontList::Count::get()
{
	return (Int32) GetNative<IDWriteFontList>()->GetFontCount();
}

Font^ FontList::default::get(Int32 index)
{
	IDWriteFont* font;
	
	ComUtils::CheckResult(
		GetNative<IDWriteFontList>()->GetFont(
			index,
			&font));

	return gcnew Font(font);
}

FontCollection^ FontList::Parent::get()
{
	IDWriteFontCollection* fontCollection;

	ComUtils::CheckResult(
		GetNative<IDWriteFontList>()->GetFontCollection(
			&fontCollection));

	return gcnew FontCollection(fontCollection);
}
