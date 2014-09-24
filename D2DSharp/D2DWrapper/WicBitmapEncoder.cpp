/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicBitmapEncoder.h"

using namespace Managed::Graphics::Imaging;

WicBitmapFrameEncode^ WicBitmapEncoder::CreateNewFrame()
{
	IWICBitmapFrameEncode *frameEncode;
	ComUtils::CheckResult(GetNative<IWICBitmapEncoder>()->CreateNewFrame(&frameEncode, NULL));
	return gcnew WicBitmapFrameEncode(frameEncode);
}

//WicBitmapFrameEncode^ CreateNewFrame(out PropertyBag2^ encoderOptions);
WicBitmapEncoderInfo^ WicBitmapEncoder::EncoderInfo::get()
{
	IWICBitmapEncoderInfo* ptr;
	ComUtils::CheckResult(GetNative<IWICBitmapEncoder>()->GetEncoderInfo(&ptr));
	return gcnew WicBitmapEncoderInfo(ptr);
}

WicMetadataQueryWriter^ WicBitmapEncoder::MetadataQueryWriter::get()
{
	IWICMetadataQueryWriter* ptr;
	ComUtils::CheckResult(GetNative<IWICBitmapEncoder>()->GetMetadataQueryWriter(&ptr));
	return gcnew WicMetadataQueryWriter(ptr);
}

void WicBitmapEncoder::Initialize(Stream^ stream, BitmapEncoderCacheOption cacheOptions)
{
	throw gcnew NotImplementedException();
}

void WicBitmapEncoder::SetColorContexts(array<WicColorContext^>^ colorContext)
{
	throw gcnew NotImplementedException();
}

void WicBitmapEncoder::SetPalette(WicPalette^ palette)
{
	ComUtils::CheckResult(GetNative<IWICBitmapEncoder>()->SetPalette(palette->GetNative<IWICPalette>()));
}

void WicBitmapEncoder::SetPreview(WicBitmapSource^ preview)
{
	ComUtils::CheckResult(GetNative<IWICBitmapEncoder>()->SetPreview(preview->GetNative<IWICBitmapSource>()));
}

void WicBitmapEncoder::SetThumbnail(WicBitmapSource^ thumbnail)
{
	ComUtils::CheckResult(GetNative<IWICBitmapEncoder>()->SetThumbnail(thumbnail->GetNative<IWICBitmapSource>()));
}

