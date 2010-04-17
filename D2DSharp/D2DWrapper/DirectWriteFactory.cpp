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

		HRESULT hr = DWriteCreateFactory(
			(DWRITE_FACTORY_TYPE)factoryType, 
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&writeFactory));

		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew DirectWriteFactory(writeFactory);
	}

	TextFormat^ DirectWriteFactory::CreateTextFormat(String^ fontFamilyName, FontCollection^ fontCollection, FontWeight fontWeight, FontStyle fontStyle, FontStretch fontStretch, FLOAT fontSize, String^ localeName)
	{
		if(fontFamilyName == nullptr)
			throw gcnew ArgumentNullException("fontFamilyName");

		pin_ptr<const System::Char> pFontFamily = PtrToStringChars(fontFamilyName);
		
		pin_ptr<const System::Char> pLocaleName = localeName == nullptr ? L"" : PtrToStringChars(fontFamilyName);
		
		IDWriteFontCollection* pFontCollection = fontCollection == nullptr ? NULL : fontCollection->GetNative();
		
		IDWriteTextFormat *textFormat;

		HRESULT hr = GetNative()->CreateTextFormat(
			pFontFamily, 
			pFontCollection, 
			(DWRITE_FONT_WEIGHT)fontWeight, 
			(DWRITE_FONT_STYLE)fontStyle,
			(DWRITE_FONT_STRETCH)fontStretch,
			fontSize,
			pLocaleName,
			&textFormat);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew TextFormat(textFormat);
	}
	
	TextLayout^ DirectWriteFactory::CreateTextLayout(String^ string, TextFormat^ textFormat, FLOAT maxWidth, FLOAT maxHeight)
	{
		pin_ptr<const System::Char> pString = PtrToStringChars(string);
		IDWriteTextLayout* textLayout;
		HRESULT hr = GetNative()->CreateTextLayout(
			pString,
			string->Length,
			textFormat->GetNative(),
			maxWidth,
			maxHeight,
			&textLayout);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew TextLayout(textLayout);
	}
}}}