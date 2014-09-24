/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "Stdafx.h"

#include "WicBitmapCodecInfo.h"

namespace Managed { namespace Graphics { namespace Imaging
{
	bool WicBitmapCodecInfo::DoesSupportAnimation::get()
	{
		BOOL value;
		ComUtils::CheckResult(GetNative<IWICBitmapCodecInfo>()->DoesSupportAnimation(&value));
		return value != 0;
	}

	bool WicBitmapCodecInfo::DoesSupportChromakey::get()
	{
		BOOL value;
		ComUtils::CheckResult(GetNative<IWICBitmapCodecInfo>()->DoesSupportChromakey(&value));
		return value != 0;
	}

	bool WicBitmapCodecInfo::DoesSupportLossless::get()
	{
		BOOL value;
		ComUtils::CheckResult(GetNative<IWICBitmapCodecInfo>()->DoesSupportLossless(&value));
		return value != 0;
	}

	bool WicBitmapCodecInfo::DoesSupportMultiframe::get()
	{
		BOOL value;
		ComUtils::CheckResult(GetNative<IWICBitmapCodecInfo>()->DoesSupportMultiframe(&value));
		return value != 0;
	}

	String^ WicBitmapCodecInfo::ColorManagementVersion::get()
	{
		UINT chActual;
		IWICBitmapCodecInfo* ptr = GetNative<IWICBitmapCodecInfo>();
		ComUtils::CheckResult(ptr->GetColorManagementVersion(0, NULL, &chActual));
		wchar_t* text = new wchar_t[chActual + 1];
		try
		{
			ComUtils::CheckResult(ptr->GetColorManagementVersion(chActual, text, &chActual));
			return gcnew String(text);
		}
		finally
		{
			delete text;
		}
	}

	Guid WicBitmapCodecInfo::ContainerFormat::get()
	{
		Guid guid;
		ComUtils::CheckResult(GetNative<IWICBitmapCodecInfo>()->GetContainerFormat((GUID*) &guid));
		return guid;
	}

	String^ WicBitmapCodecInfo::DeviceManufacturer::get()
	{
		UINT chActual;
		IWICBitmapCodecInfo* ptr = GetNative<IWICBitmapCodecInfo>();
		ComUtils::CheckResult(ptr->GetDeviceManufacturer(0, NULL, &chActual));
		wchar_t* text = new wchar_t[chActual + 1];
		try
		{
			ComUtils::CheckResult(ptr->GetDeviceManufacturer(chActual, text, &chActual));
			return gcnew String(text);
		}
		finally
		{
			delete text;
		}
	}

	String^ WicBitmapCodecInfo::DeviceModels::get()
	{
		UINT chActual;
		IWICBitmapCodecInfo* ptr = GetNative<IWICBitmapCodecInfo>();
		ComUtils::CheckResult(ptr->GetDeviceModels(0, NULL, &chActual));
		wchar_t* text = new wchar_t[chActual + 1];
		try
		{
			ComUtils::CheckResult(ptr->GetDeviceModels(chActual, text, &chActual));
			return gcnew String(text);
		}
		finally
		{
			delete text;
		}
	}

	String^ WicBitmapCodecInfo::FileExtensions::get()
	{
		UINT chActual;
		IWICBitmapCodecInfo* ptr = GetNative<IWICBitmapCodecInfo>();
		ComUtils::CheckResult(ptr->GetFileExtensions(0, NULL, &chActual));
		wchar_t* text = new wchar_t[chActual + 1];
		try
		{
			ComUtils::CheckResult(ptr->GetFileExtensions(chActual, text, &chActual));
			return gcnew String(text);
		}
		finally
		{
			delete text;
		}
	}

	String^ WicBitmapCodecInfo::MimeTypes::get()
	{
		UINT chActual;
		IWICBitmapCodecInfo* ptr = GetNative<IWICBitmapCodecInfo>();
		ComUtils::CheckResult(ptr->GetMimeTypes(0, NULL, &chActual));
		wchar_t* text = new wchar_t[chActual + 1];
		try
		{
			ComUtils::CheckResult(ptr->GetMimeTypes(chActual, text, &chActual));
			return gcnew String(text);
		}
		finally
		{
			delete text;
		}
	}

	array<Guid>^ WicBitmapCodecInfo::PixelFormats::get()
	{
		throw gcnew NotImplementedException();
	}

	bool WicBitmapCodecInfo::MatchesMimeType(String^ mimeType)
	{
		BOOL value;
		pin_ptr<const wchar_t> pMimeType = PtrToStringChars(mimeType);
		ComUtils::CheckResult(GetNative<IWICBitmapCodecInfo>()->MatchesMimeType(pMimeType, &value));
		return value != 0;
	}
}}}