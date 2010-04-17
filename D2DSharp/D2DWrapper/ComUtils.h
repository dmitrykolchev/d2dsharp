/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Runtime { namespace InteropServices
{
	ref class ComUtils
	{
	private:
		ComUtils()
		{
		}
	public:
		static void CheckResult(HRESULT hr)
		{
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}
	};
}}}