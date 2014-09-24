/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "WicComponentInfo.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
{
	public ref class WicBitmapCodecInfo: WicComponentInfo
	{
	internal:
		WicBitmapCodecInfo(IWICBitmapCodecInfo* native): WicComponentInfo(native)
		{
		}
	public:
		property bool DoesSupportAnimation { bool get(); }
		property bool DoesSupportChromakey { bool get(); }
		property bool DoesSupportLossless { bool get(); }
		property bool DoesSupportMultiframe { bool get(); }
		property String^ ColorManagementVersion { String^ get(); }
		property Guid ContainerFormat { Guid get(); }
		property String^ DeviceManufacturer { String^ get(); }
		property String^ DeviceModels { String^ get(); }
		property String^ FileExtensions { String^ get(); }
		property String^ MimeTypes { String^ get(); }
		property array<Guid>^ PixelFormats { array<Guid>^ get(); }
		bool MatchesMimeType(String^ mimeType);
	};
}}}