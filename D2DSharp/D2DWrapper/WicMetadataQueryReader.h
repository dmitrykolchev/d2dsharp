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
	public ref class WicMetadataQueryReader: ComWrapper
	{
	internal:
		WicMetadataQueryReader(IWICMetadataQueryReader* native): ComWrapper(native)
		{
		}
	public:
		property Guid ContainerFormat { Guid get(); }
		property String^ Location { String^ get(); }
		Object^ GetMetadataByName(String^ name);
		//TODO: array<String^>^ GetEnumerator();
	};
}}}