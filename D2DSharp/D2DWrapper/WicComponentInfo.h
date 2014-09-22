/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once


namespace Managed { namespace Graphics { namespace Imaging
{
	public ref class WicComponentInfo: ComWrapper
	{
	internal:
		WicComponentInfo(IWICComponentInfo* native): ComWrapper(native)
		{
		}
	public:
	};
}}}