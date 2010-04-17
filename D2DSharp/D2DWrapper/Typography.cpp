#include "Stdafx.h"

using namespace Managed::Graphics::DirectWrite;

void Typography::AddFontFeature(FontFeature fontFeature)
{
	ComUtils::CheckResult(GetNative()->AddFontFeature(*(DWRITE_FONT_FEATURE*)&fontFeature));
}

void Typography::AddFontFeature(FontFeatureTag nameTag, UInt32 value)
{
	AddFontFeature(FontFeature(nameTag, value));
}

array<FontFeature>^ Typography::GetFontFeatures()
{
	IDWriteTypography* native = GetNative();
	UINT32 count = native->GetFontFeatureCount();
	array<FontFeature>^ features = gcnew array<FontFeature>(count);
	pin_ptr<FontFeature> pFeatures = &features[0];
	for(UINT32 index = 0; index < count; ++index, pFeatures++)
	{
		ComUtils::CheckResult(native->GetFontFeature(index, (DWRITE_FONT_FEATURE*)pFeatures));
	}
	return features;
}
