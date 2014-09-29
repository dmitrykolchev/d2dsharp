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
			if (addRef)
				native->AddRef();
		}
		void Attach(IUnknown* native)
		{
			if (_native != NULL)
				reinterpret_cast<IUnknown*>(_native)->Release();
			_native = native;
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
				reinterpret_cast<IUnknown*>(_native)->Release();
				_native = NULL;
			}
		}
	internal:
		template<class Interface> 
		inline Interface* GetNative()
		{
			return reinterpret_cast<Interface*>(_native);
		}
		void* _native;
	};
}}}