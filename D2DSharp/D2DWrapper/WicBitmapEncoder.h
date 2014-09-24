/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
{
	ref class WicBitmapFrameEncode;
	ref class WicBitmapEncoderInfo;
	ref class WicMetadataQueryWriter;
	ref class WicColorContext;
	ref class WicPalette;
	ref class WicBitmapSource;

	public ref class WicBitmapEncoder: ComWrapper
	{
	internal:
		WicBitmapEncoder(IWICBitmapEncoder* native): ComWrapper(native)
		{
		}
	public:
		void Commit()
		{
			ComUtils::CheckResult(GetNative<IWICBitmapEncoder>()->Commit());
		}
		WicBitmapFrameEncode^ CreateNewFrame();
		//WicBitmapFrameEncode^ CreateNewFrame(out PropertyBag2^ encoderOptions);
		Guid GetContainerFormat()
		{
			Guid containerFormat;
			ComUtils::CheckResult(GetNative<IWICBitmapEncoder>()->GetContainerFormat((GUID*) &containerFormat));
			return containerFormat;
		}
		property WicBitmapEncoderInfo^ EncoderInfo { WicBitmapEncoderInfo^ get(); }
		property WicMetadataQueryWriter^ MetadataQueryWriter { WicMetadataQueryWriter^ get(); }
		void Initialize(Stream^ stream, BitmapEncoderCacheOption cacheOptions);
		void SetColorContexts(array<WicColorContext^>^ colorContext);
		void SetPalette(WicPalette^ palette);
		void SetPreview(WicBitmapSource^ preview);
		void SetThumbnail(WicBitmapSource^ thumbnail);
	};
}}}