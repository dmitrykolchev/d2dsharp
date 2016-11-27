/*
* Dxgi.h
*
* Authors:
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed {
	namespace Graphics {
		namespace Dxgi
		{
			public ref class DxgiObject abstract: ComWrapper
			{
			protected:
				DxgiObject(IDXGIObject* native ): ComWrapper(native)
				{
				}
			public:

			};
			public ref class DxgiDeviceSubObject abstract: DxgiObject
			{
			protected:
				DxgiDeviceSubObject(IDXGIDeviceSubObject* native): DxgiObject(native)
				{
				}
			public:

			};
			public ref class DxgiSurface: DxgiDeviceSubObject
			{
			internal:
				DxgiSurface(IDXGISurface* native):DxgiDeviceSubObject(native)
				{
				}
			public:

			};
		}
	}
}
