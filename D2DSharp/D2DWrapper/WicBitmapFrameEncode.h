/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
{
	ref class WicMetadataQueryWriter;
	ref class WicColorContext;
	ref class WicBitmapSource;

	public ref class WicBitmapFrameEncode: ComWrapper
	{
	internal:
		WicBitmapFrameEncode(IWICBitmapFrameEncode* native): ComWrapper(native)
		{
		}
	public:
		void Commit()
		{
			ComUtils::CheckResult(GetNative<IWICBitmapFrameEncode>()->Commit());
		}
		//WicMetadataQueryWriter^ GetMetadataQueryWriter();
		//TODO: void Initialize(PropertyBag2^ encoderOptions);
		//void SetColorContexts(array<WicColorContext^>^ colorContext);
		//void SetPalette(WicPalette^ palette);
		//TODO: void SetPixelFormat()
		//void SetResolution(double dpiX, double dpiY);
		//void SetSize(int width, int height);
		//void SetThumbnail(WicBitmapSource^ thumbnail);
		//void WritePixels(int lineCount, int stride, array<Byte>^ pixels);
		//void WriteSource(WicBitmapSource^ source, WicRect rect);
	};
}}}