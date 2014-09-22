#pragma once


#include "ComWrapper.h"
#include "DWCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed { namespace Graphics { namespace DirectWrite 
{
	public ref class RenderingParams: ComWrapper
	{
	internal:
		RenderingParams(IDWriteRenderingParams* native): ComWrapper(native)
		{
		}
	public:
		property Single ClearTypeLevel { Single get() { return GetNative<IDWriteRenderingParams>()->GetClearTypeLevel(); } }
		property Single EnhancedContrast { Single get() { return GetNative<IDWriteRenderingParams>()->GetEnhancedContrast(); } }
		property Single Gamma { Single get() { return GetNative<IDWriteRenderingParams>()->GetGamma(); } }
		property Managed::Graphics::DirectWrite::PixelGeometry PixelGeometry 
		{ 
			Managed::Graphics::DirectWrite::PixelGeometry  get()
			{
				return (Managed::Graphics::DirectWrite::PixelGeometry)GetNative<IDWriteRenderingParams>()->GetPixelGeometry();
			}
		}
		property Managed::Graphics::DirectWrite::RenderingMode RenderingMode
		{ 
			Managed::Graphics::DirectWrite::RenderingMode  get()
			{
				return (Managed::Graphics::DirectWrite::RenderingMode)GetNative<IDWriteRenderingParams>()->GetRenderingMode();
			}
		}
	};
}}}