#include "Stdafx.h"

using namespace Managed::Graphics::DirectWrite;


Boolean FontFile::Analyze([Out]FontFileType% fontFileType, [Out]FontFaceType% fontFaceType, [Out]UInt32% numberOfFaces)
{
	BOOL isSupportedFontType;
	DWRITE_FONT_FILE_TYPE fontFileType_;
	DWRITE_FONT_FACE_TYPE fontFaceType_;
	UINT32 numberOfFaces_;
	ComUtils::CheckResult(
		GetNative<IDWriteFontFile>()->Analyze(
			&isSupportedFontType,
			&fontFileType_,
			&fontFaceType_,
			&numberOfFaces_));
	fontFileType = (FontFileType)fontFileType_;
	fontFaceType = (FontFaceType)fontFaceType_;
	numberOfFaces = numberOfFaces_;

	return isSupportedFontType != 0;
}

FontFileLoader^ FontFile::GetLoader()
{
	IDWriteFontFileLoader* fontFileLoader;

	ComUtils::CheckResult(
		GetNative<IDWriteFontFile>()->GetLoader(
			&fontFileLoader));
	return gcnew FontFileLoader(fontFileLoader);
}

array<Byte>^ FontFile::GetReferenceKey()
{
	void* fontFileReferenceKey;
	UINT32 fontFileReferenceKeySize;

	ComUtils::CheckResult(
		GetNative<IDWriteFontFile>()->GetReferenceKey(
			(const void**)&fontFileReferenceKey,
			&fontFileReferenceKeySize));

	array<Byte>^ key = gcnew array<Byte>(fontFileReferenceKeySize);
	pin_ptr<Byte> pKey = &key[0];
	memcpy(pKey, fontFileReferenceKey, fontFileReferenceKeySize);
	return key;
}
