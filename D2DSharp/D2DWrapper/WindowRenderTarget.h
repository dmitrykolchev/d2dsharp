/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "RenderTarget.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	[FlagsAttribute()]
	public enum class WindowState
	{
		None = 0x0000000,
		Occluded = 0x0000001,
	};


	ref class SolidColorBrush;
	[System::Security::SuppressUnmanagedCodeSecurity]
	public ref class WindowRenderTarget: RenderTarget
	{
	internal:
		WindowRenderTarget(ID2D1HwndRenderTarget* renderTarget): RenderTarget(renderTarget)
		{
		}

	public:
		property WindowState State
		{
			WindowState get()
			{
				int state = GetNative<ID2D1HwndRenderTarget>()->CheckWindowState();
				return (WindowState)state;
			}
		}

		property IntPtr Handle
		{
			IntPtr get()
			{
				HWND hwnd = GetNative<ID2D1HwndRenderTarget>()->GetHwnd();
				return IntPtr((void*)hwnd);
			}
		}

		void Resize(SizeU size)
		{
			ComUtils::CheckResult(GetNative<ID2D1HwndRenderTarget>()->Resize(reinterpret_cast<D2D1_SIZE_U*>(&size)));
		}
	};
}}}