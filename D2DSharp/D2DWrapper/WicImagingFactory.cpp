/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicImagingFactory.h"
#include "WicBitmapDecoder.h"

namespace Managed { namespace Graphics { namespace Imaging
{
	WicBitmapDecoder^ WicImagingFactory::CreateDecoder(String^ fileName, Guid vendor, DesiredAccess desiredAccess, DecodeOptions options)
	{
		pin_ptr<const System::Char> pFileName = PtrToStringChars(fileName);
		GUID *pGuid = vendor == Guid::Empty ? NULL : (GUID*)&vendor;
		IWICBitmapDecoder* decoder;
		ComUtils::CheckResult(GetNative()->CreateDecoderFromFilename(pFileName, pGuid, (DWORD)desiredAccess, (WICDecodeOptions)options, &decoder));
		return gcnew WicBitmapDecoder(decoder);
	}

	WicBitmapDecoder^ WicImagingFactory::CreateDecoder(WicStream^ stream, Guid vendor, DecodeOptions options)
	{
		GUID *pGuid = vendor == Guid::Empty ? NULL : (GUID*)&vendor;
		IWICBitmapDecoder* decoder;
		ComUtils::CheckResult(GetNative()->CreateDecoderFromStream(
			(IStream*)stream->GetNative(),
			pGuid,
			(WICDecodeOptions)options,
			&decoder)
			);
		return gcnew WicBitmapDecoder(decoder);
	}

	WicStream^ WicImagingFactory::CreateStream()
	{
		IWICStream *stream;
		ComUtils::CheckResult(GetNative()->CreateStream(&stream));
		return gcnew WicStream(stream);
	}

}}}