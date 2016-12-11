#pragma once

#include "ComWrapper.h"
#include <D3D11.h>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Managed::Runtime::InteropServices;

namespace Managed {
	namespace Graphics {
		namespace D3D11
		{
			public ref class DeviceChild: ComWrapper {
			internal:
				DeviceChild(ID3D11DeviceChild* native) : ComWrapper(native)
				{

				}
			};

			public ref class Resource : DeviceChild {
			internal:
				Resource(ID3D11Resource* native) : DeviceChild(native)
				{

				}
			};

			public ref class Texture2D: Resource
			{
			internal:
				Texture2D(ID3D11Texture2D* native) : Resource(native)
				{

				}
			};
		}
	}
}

