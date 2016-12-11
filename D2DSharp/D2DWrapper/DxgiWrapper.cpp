#include "Stdafx.h"
#include "DxgiWrapper.h"

#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "dxgi.lib")

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Managed {
	namespace Graphics {
		namespace Dxgi
		{
			void DxgiFactory::MakeWindowAssociation(IntPtr windowHandle, int flags)
			{
				throw gcnew NotImplementedException();
			}

			DxgiSwapChain1^ DxgiFactory::CreateSwapChainForHwnd(ComWrapper^ device, IntPtr hwnd)
			{
				IDXGIFactory *factory = GetNative<IDXGIFactory>();
				IDXGIFactory2 *factory2;
				ComUtils::CheckResult(factory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&factory2)));

				DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
				ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
				swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
				swapChainDesc.SampleDesc.Count = 1;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.BufferCount = 2;
				IDXGISwapChain1* swapChain1;
				HRESULT hr = factory2->CreateSwapChainForHwnd(
					device->GetNative<IUnknown>(),
					(HWND)hwnd.ToPointer(),
					&swapChainDesc,
					nullptr,
					nullptr,
					&swapChain1);
				
				factory2->Release();
				ComUtils::CheckResult(hr);
				return gcnew DxgiSwapChain1(swapChain1);
			}
			
			DxgiSwapChain1^ DxgiFactory::CreateSwapChainForHwnd(ComWrapper^ device, IntPtr hwnd, DxgiSwapChainDesc1 desc)
			{
				IDXGIFactory *factory = GetNative<IDXGIFactory>();
				IDXGIFactory2 *factory2;
				ComUtils::CheckResult(factory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&factory2)));
				IDXGISwapChain1* swapChain1;
				DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
				ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
				swapChainDesc.Width = desc.Width;
				swapChainDesc.Height = desc.Height;
				swapChainDesc.Format = (DXGI_FORMAT)desc.Format;
				swapChainDesc.SampleDesc.Count = desc.SampleDesc.Count;
				swapChainDesc.SampleDesc.Quality = desc.SampleDesc.Quality;
				swapChainDesc.BufferUsage = (DXGI_USAGE)desc.BufferUsage;
				swapChainDesc.BufferCount = desc.BufferCount;

				HRESULT hr = factory2->CreateSwapChainForHwnd(
					device->GetNative<IUnknown>(),
					(HWND)hwnd.ToPointer(),
					&swapChainDesc,
					nullptr,
					nullptr,
					&swapChain1);
				factory2->Release();
				ComUtils::CheckResult(hr);
				return gcnew DxgiSwapChain1(swapChain1);
			}

			DxgiSwapChain1^ DxgiFactory::CreateSwapChainForHwnd(ComWrapper^ device, IntPtr hwnd, DxgiSwapChainDesc1 desc,
				DxgiSwapChainFullscreenDesc fullscreenDesc)
			{
				IDXGIFactory *factory = GetNative<IDXGIFactory>();
				IDXGIFactory2 *factory2;
				ComUtils::CheckResult(factory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&factory2)));
				IDXGISwapChain1* swapChain1;
				HRESULT hr = factory2->CreateSwapChainForHwnd(
					device->GetNative<IUnknown>(), 
					(HWND)hwnd.ToPointer(),
					reinterpret_cast<DXGI_SWAP_CHAIN_DESC1*>(&desc),
					reinterpret_cast<DXGI_SWAP_CHAIN_FULLSCREEN_DESC*>(&fullscreenDesc),
					nullptr,
					&swapChain1);
				factory2->Release();
				ComUtils::CheckResult(hr);
				return gcnew DxgiSwapChain1(swapChain1);
			}

			IntPtr GetWindowAssociation()
			{
				throw gcnew NotImplementedException();
			}
			DxgiAdapter^ CreateSoftwareAdapter(IntPtr module)
			{
				throw gcnew NotImplementedException();
			}

			DxgiSurface^ DxgiDevice::CreateSurface(DxgiSurfaceDescription description, int numSurfaces, DxgiUsage usage, DxgiSharedResource sharedResource)
			{
				IDXGISurface* surface;
				ComUtils::CheckResult(GetNative<IDXGIDevice>()->CreateSurface(
					(DXGI_SURFACE_DESC*)&description, numSurfaces, (DXGI_USAGE)usage, (DXGI_SHARED_RESOURCE*)&sharedResource, &surface));
				return gcnew DxgiSurface(surface);
			}

			DxgiDevice^ DxgiDevice::CreateDevice()
			{
				ID3D11Device *device;
				UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT |
					D3D11_CREATE_DEVICE_DEBUG;

				HRESULT hr = CreateD3DDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, flags, &device);
				if (FAILED(hr))
				{
					ComUtils::CheckResult(CreateD3DDevice(nullptr, D3D_DRIVER_TYPE_WARP, flags, &device));
				}
				IDXGIDevice *dxgiDevice;
				hr = device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
				device->Release();
				ComUtils::CheckResult(hr);
				return gcnew DxgiDevice(dxgiDevice);
			}

			HRESULT DxgiDevice::CreateD3DDevice(
				IDXGIAdapter *adapter,
				D3D_DRIVER_TYPE driverType,
				UINT flags,
				ID3D11Device **ppDevice
			)
			{
				static const D3D_FEATURE_LEVEL featureLevels[] =
				{
					D3D_FEATURE_LEVEL_11_0,
					D3D_FEATURE_LEVEL_10_1,
					D3D_FEATURE_LEVEL_10_0,
					D3D_FEATURE_LEVEL_9_3,
					D3D_FEATURE_LEVEL_9_2,
					D3D_FEATURE_LEVEL_9_1,
				};
				UINT numFeatureLevels = ARRAYSIZE(featureLevels);

				ID3D11Device *device;
				D3D_FEATURE_LEVEL createdFeatureLevel;


				HRESULT hr = D3D11CreateDevice(
					adapter,
					driverType,
					nullptr,
					flags,
					featureLevels,
					numFeatureLevels,
					D3D11_SDK_VERSION,
					&device,
					&createdFeatureLevel,
					nullptr
				);
				if(SUCCEEDED(hr))
					*ppDevice = device;
				return hr;
			}
			void DxgiSwapChain::GetBuffer(int buffer, [OutAttribute]DxgiSurface^% value)
			{
				value = gcnew DxgiSurface(GetBuffer<IDXGISurface>(buffer));
			}
			void DxgiSwapChain::GetBuffer(int buffer, [OutAttribute]Managed::Graphics::D3D11::Texture2D^% value)
			{
				value = gcnew Managed::Graphics::D3D11::Texture2D(GetBuffer<ID3D11Texture2D>(buffer));
			}
			template<class T>
			T* DxgiSwapChain::GetBuffer(int buffer)
			{
				T *result;
				ComUtils::CheckResult(GetNative<IDXGISwapChain>()->GetBuffer(buffer, __uuidof(T), reinterpret_cast<void**>(&result)));
				return result;
			}
		}
	}
}