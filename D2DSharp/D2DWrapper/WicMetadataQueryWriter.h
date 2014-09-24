/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "WicMetadataQueryReader.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
{
	public ref class WicMetadataQueryWriter: WicMetadataQueryReader
	{
	internal:
		WicMetadataQueryWriter(IWICMetadataQueryWriter* native): WicMetadataQueryReader(native)
		{
		}
	public:
		void RemoveMetadataByName(String^ name);
		void SetMetadataByName(String^ name, Object^ value);
	};
}}}