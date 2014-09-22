#include "Stdafx.h"

using namespace Managed::Graphics::DirectWrite;

FontFileStream^ FontFileLoader::CreateStreamFromKey(array<Byte>^ fontFileReferenceKey)
{
	IDWriteFontFileStream* stream;
	
	pin_ptr<Byte> pKey = &fontFileReferenceKey[0];

	ComUtils::CheckResult(
		GetNative<IDWriteFontFileLoader>()->CreateStreamFromKey(
			pKey,
			fontFileReferenceKey->Length,
			&stream));

	return gcnew FontFileStream(stream);
}