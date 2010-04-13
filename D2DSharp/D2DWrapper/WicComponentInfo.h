#pragma once


namespace DykBits { namespace Graphics { namespace Imaging
{
	public ref class WicComponentInfo: ComWrapper
	{
	internal:
		WicComponentInfo(IWICComponentInfo* native): ComWrapper(native)
		{
		}
	internal:
		IWICComponentInfo* GetNative()
		{
			return (IWICComponentInfo*)ComWrapper::GetNative();
		}
	};
}}}