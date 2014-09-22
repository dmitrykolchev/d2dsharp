/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicImagingFactory.h"
#include "WicBitmapDecoder.h"
#include "WicBitmapEncoder.h"

namespace Managed { namespace Graphics { namespace Imaging
{
	WicBitmapDecoder^ WicImagingFactory::CreateDecoder(String^ fileName, Guid vendor, DesiredAccess desiredAccess, DecodeOptions options)
	{
		pin_ptr<const System::Char> pFileName = PtrToStringChars(fileName);
		GUID *pGuid = vendor == Guid::Empty ? NULL : (GUID*)&vendor;
		IWICBitmapDecoder* decoder;
		ComUtils::CheckResult(GetNative<IWICImagingFactory>()->CreateDecoderFromFilename(pFileName, pGuid, (DWORD)desiredAccess, (WICDecodeOptions)options, &decoder));
		return gcnew WicBitmapDecoder(decoder);
	}

	WicBitmapDecoder^ WicImagingFactory::CreateDecoder(WicStream^ stream, Guid vendor, DecodeOptions options)
	{
		GUID *pGuid = vendor == Guid::Empty ? NULL : (GUID*)&vendor;
		IWICBitmapDecoder* decoder;
		ComUtils::CheckResult(GetNative<IWICImagingFactory>()->CreateDecoderFromStream(
			(IStream*)stream->GetNative<IWICStream>(),
			pGuid,
			(WICDecodeOptions)options,
			&decoder)
			);
		return gcnew WicBitmapDecoder(decoder);
	}

	WicBitmapEncoder^ WicImagingFactory::CreateEncoder(Guid container)
	{
		IWICBitmapEncoder* encoder;
		ComUtils::CheckResult(GetNative<IWICImagingFactory>()->CreateEncoder(
			*(GUID*)&container,
			nullptr,
			&encoder)
			);
		return gcnew WicBitmapEncoder(encoder);
	}

	WicBitmapEncoder^ WicImagingFactory::CreateEncoder(Guid container, Guid vendor)
	{
		GUID *pGuid = vendor == Guid::Empty ? NULL : (GUID*)&vendor;
		IWICBitmapEncoder* encoder;
		ComUtils::CheckResult(GetNative<IWICImagingFactory>()->CreateEncoder(
			*(GUID*)&container,
			pGuid,
			&encoder)
			);
		return gcnew WicBitmapEncoder(encoder);
	}

	WicStream^ WicImagingFactory::CreateStream()
	{
		IWICStream *stream;
		ComUtils::CheckResult(GetNative<IWICImagingFactory>()->CreateStream(&stream));
		return gcnew WicStream(stream);
	}

}}}