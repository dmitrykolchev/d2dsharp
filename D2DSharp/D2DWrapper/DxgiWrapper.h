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
#include "DxgiCommon.h"
#include "D3DWrapper.h"

using namespace System;
using namespace System::Runtime::InteropServices;


namespace Managed {
	namespace Graphics {
		namespace Dxgi
		{
			public ref class DxgiObject abstract : ComWrapper
			{
			protected:
				DxgiObject(IDXGIObject* native) : ComWrapper(native)
				{
				}
			public:

			};
			public ref class DxgiDeviceSubObject abstract : DxgiObject
			{
			protected:
				DxgiDeviceSubObject(IDXGIDeviceSubObject* native) : DxgiObject(native)
				{
				}
			public:

			};
			public ref class DxgiSurface : DxgiDeviceSubObject
			{
			internal:
				DxgiSurface(IDXGISurface* native) :DxgiDeviceSubObject(native)
				{
				}
			public:

			};

			ref class DxgiAdapter;
			ref class DxgiSwapChain;
			ref class DxgiSwapChain1;

			public ref class DxgiFactory : DxgiObject
			{
			internal:
				DxgiFactory(IDXGIFactory* native) : DxgiObject(native)
				{

				}
			public:
				void MakeWindowAssociation(IntPtr windowHandle, int flags);
				IntPtr GetWindowAssociation() {
					HWND hwnd;
					ComUtils::CheckResult(GetNative<IDXGIFactory>()->GetWindowAssociation(&hwnd));
					return IntPtr((void*)hwnd);
				}
				DxgiSwapChain1^ CreateSwapChainForHwnd(ComWrapper^ device, IntPtr hwnd, DxgiSwapChainDesc1 desc, DxgiSwapChainFullscreenDesc fuulscreenDesc);
				DxgiSwapChain1^ CreateSwapChainForHwnd(ComWrapper^ device, IntPtr hwnd, DxgiSwapChainDesc1 desc);
				DxgiSwapChain1^ CreateSwapChainForHwnd(ComWrapper^ device, IntPtr hwnd);
			};


			public ref class DxgiAdapter : DxgiObject
			{
			internal:
				DxgiAdapter(IDXGIAdapter *adapter) : DxgiObject(adapter)
				{
				}
			public:
				property DxgiFactory^ Factory {
					DxgiFactory^ get() {
						IDXGIFactory *factory;
						ComUtils::CheckResult(GetNative<IDXGIAdapter>()->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory)));
						return gcnew DxgiFactory(factory);
					}
				}
			};

			public ref class DxgiDevice : DxgiObject
			{
			internal:
				DxgiDevice(IDXGIDevice* native) : DxgiObject(native)
				{
				}
			public:
				static DxgiDevice^ CreateDevice();

				property DxgiAdapter^ Adapter
				{
					DxgiAdapter^ get() {
						IDXGIAdapter* adapter;
						ComUtils::CheckResult(this->GetNative<IDXGIDevice>()->GetAdapter(&adapter));
						return gcnew DxgiAdapter(adapter);
					}
				}

				property int MaximumFrameLatency
				{
					int get() {
						IDXGIDevice* device = GetNative<IDXGIDevice>();
						IDXGIDevice1* device1;
						ComUtils::CheckResult(device->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&device1)));
						UINT value;
						HRESULT hr = device1->GetMaximumFrameLatency(&value);
						device1->Release();
						ComUtils::CheckResult(hr);
						return (int)value;
					}
					void set(int value)
					{
						IDXGIDevice* device = GetNative<IDXGIDevice>();
						IDXGIDevice1* device1;
						ComUtils::CheckResult(device->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(&device1)));
						HRESULT hr = device1->SetMaximumFrameLatency((UINT)value);
						device1->Release();
						ComUtils::CheckResult(hr);
					}
				}

				property int GPUThreadPriority {
					int get()
					{
						INT priority;
						this->GetNative<IDXGIDevice>()->GetGPUThreadPriority(&priority);
						return priority;
					}
					void set(int value)
					{
						this->GetNative<IDXGIDevice>()->SetGPUThreadPriority(value);
					}
				}
				DxgiSurface^ CreateSurface(DxgiSurfaceDescription description, int numSurfaces, DxgiUsage usage, DxgiSharedResource shredResource);
			private:
				static HRESULT CreateD3DDevice(IDXGIAdapter* adapter, D3D_DRIVER_TYPE driverType, UINT flags, ID3D11Device **ppDevice);
			};

			public ref class DxgiSwapChain : DxgiDeviceSubObject
			{
			internal:
				DxgiSwapChain(IDXGISwapChain* native) : DxgiDeviceSubObject(native)
				{
				}
			public:
				void Present(int syncInterval, DxgiPresent flags)
				{
					ComUtils::CheckResult(GetNative<IDXGISwapChain>()->Present((UINT)syncInterval, (UINT)flags));
				}
				void GetBuffer(int buffer, [OutAttribute]DxgiSurface^% value);
				void GetBuffer(int buffer, [OutAttribute]Managed::Graphics::D3D11::Texture2D^% value);
				void ResizeBuffers()
				{
					ComUtils::CheckResult(GetNative<IDXGISwapChain>()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));
				}
			private:
				template<class I>
				I* GetBuffer(int buffer);
				//virtual HRESULT STDMETHODCALLTYPE GetBuffer(
				//	/* [in] */ UINT Buffer,
				//	/* [annotation][in] */
				//	_In_  REFIID riid,
				//	/* [annotation][out][in] */
				//	_COM_Outptr_  void **ppSurface) = 0;

				//virtual HRESULT STDMETHODCALLTYPE SetFullscreenState(
				//	/* [in] */ BOOL Fullscreen,
				//	/* [annotation][in] */
				//	_In_opt_  IDXGIOutput *pTarget) = 0;

				//virtual HRESULT STDMETHODCALLTYPE GetFullscreenState(
				//	/* [annotation][out] */
				//	_Out_opt_  BOOL *pFullscreen,
				//	/* [annotation][out] */
				//	_COM_Outptr_opt_result_maybenull_  IDXGIOutput **ppTarget) = 0;

				//virtual HRESULT STDMETHODCALLTYPE GetDesc(
				//	/* [annotation][out] */
				//	_Out_  DXGI_SWAP_CHAIN_DESC *pDesc) = 0;

				//virtual HRESULT STDMETHODCALLTYPE ResizeBuffers(
				//	/* [in] */ UINT BufferCount,
				//	/* [in] */ UINT Width,
				//	/* [in] */ UINT Height,
				//	/* [in] */ DXGI_FORMAT NewFormat,
				//	/* [in] */ UINT SwapChainFlags) = 0;

				//virtual HRESULT STDMETHODCALLTYPE ResizeTarget(
				//	/* [annotation][in] */
				//	_In_  const DXGI_MODE_DESC *pNewTargetParameters) = 0;

				//virtual HRESULT STDMETHODCALLTYPE GetContainingOutput(
				//	/* [annotation][out] */
				//	_COM_Outptr_  IDXGIOutput **ppOutput) = 0;

				//virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics(
				//	/* [annotation][out] */
				//	_Out_  DXGI_FRAME_STATISTICS *pStats) = 0;

				//virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount(
				//	/* [annotation][out] */
				//	_Out_  UINT *pLastPresentCount) = 0;
			};

			public ref class DxgiSwapChain1 : DxgiSwapChain
			{
			internal:
				DxgiSwapChain1(IDXGISwapChain1* native) : DxgiSwapChain(native)
				{
				}
			public:

			};
		}
	}
}
