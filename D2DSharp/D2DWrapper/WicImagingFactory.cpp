#include "Stdafx.h"

#include "WicImagingFactory.h"
#include "WicBitmapDecoder.h"

namespace DykBits { namespace Graphics { namespace Imaging
{
	WicBitmapDecoder^ WicImagingFactory::CreateDecoderFromFilename(String^ fileName, Guid vendor, FileAccess fileAccess, DecodeOptions options)
	{
		pin_ptr<const System::Char> pFileName = PtrToStringChars(fileName);
		GUID *pGuid = vendor == Guid::Empty ? NULL : (GUID*)&vendor;
		DWORD fa = GENERIC_READ;
		switch(fileAccess)
		{
		case FileAccess::Read:
			fa = GENERIC_READ;
			break;
		case FileAccess::Write:
			fa = GENERIC_WRITE;
			break;
		case FileAccess::ReadWrite:
			fa = GENERIC_READ | GENERIC_WRITE;
			break;
		}
		IWICBitmapDecoder* decoder;
		HRESULT hr = GetNative()->CreateDecoderFromFilename(pFileName, pGuid, fa, (WICDecodeOptions)options, &decoder);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew WicBitmapDecoder(decoder);
	}

}}}