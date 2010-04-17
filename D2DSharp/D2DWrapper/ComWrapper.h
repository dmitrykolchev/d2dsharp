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
	public ref class ComWrapper
	{
	internal:
		ComWrapper(IUnknown* native)
		{
			_native = native;
		}
		ComWrapper(IUnknown* native, Boolean addRef)
		{
			_native = native;
			if(addRef)
				_native->AddRef();
		}
	public:
		~ComWrapper()
		{
			this->!ComWrapper();
		}
		!ComWrapper()
		{
			if(_native != NULL)
			{
				_native->Release();
				_native = NULL;
			}
		}
	internal:
		IUnknown* GetNative()
		{
			return _native;
		}
	private:
		IUnknown* _native;
	};
}}}