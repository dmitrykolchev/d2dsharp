#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DykBits { namespace Runtime { namespace InteropServices
{
	public ref class ComWrapper abstract
	{
	protected:
		ComWrapper(IUnknown* native)
		{
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