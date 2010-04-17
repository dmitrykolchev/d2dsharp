/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#pragma comment(lib, "d2d1.lib")

#include "StrokeStyle.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;

namespace Managed { namespace Graphics { namespace Imaging
{
	ref class WicBitmap;
}}}

using namespace Managed::Graphics::Imaging;

namespace Managed { namespace Graphics { namespace Direct2D 
{
	ref class RenderTarget;
	ref class WindowRenderTarget;
	ref class Geometry;
	ref class EllipseGeometry;
	ref class RectangleGeometry;
	ref class RoundedRectangleGeometry;
	ref class TransformedGeometry;
	ref class GeometryGroup;
	ref class DCRenderTarget;
	ref class PathGeometry;

	public enum class DxgiFormat
	{
	  UNKNOWN                      = 0,
	  R32G32B32A32_TYPELESS        = 1,
	  R32G32B32A32_FLOAT           = 2,
	  R32G32B32A32_UINT            = 3,
	  R32G32B32A32_SINT            = 4,
	  R32G32B32_TYPELESS           = 5,
	  R32G32B32_FLOAT              = 6,
	  R32G32B32_UINT               = 7,
	  R32G32B32_SINT               = 8,
	  R16G16B16A16_TYPELESS        = 9,
	  R16G16B16A16_FLOAT           = 10,
	  R16G16B16A16_UNORM           = 11,
	  R16G16B16A16_UINT            = 12,
	  R16G16B16A16_SNORM           = 13,
	  R16G16B16A16_SINT            = 14,
	  R32G32_TYPELESS              = 15,
	  R32G32_FLOAT                 = 16,
	  R32G32_UINT                  = 17,
	  R32G32_SINT                  = 18,
	  R32G8X24_TYPELESS            = 19,
	  D32_FLOAT_S8X24_UINT         = 20,
	  R32_FLOAT_X8X24_TYPELESS     = 21,
	  X32_TYPELESS_G8X24_UINT      = 22,
	  R10G10B10A2_TYPELESS         = 23,
	  R10G10B10A2_UNORM            = 24,
	  R10G10B10A2_UINT             = 25,
	  R11G11B10_FLOAT              = 26,
	  R8G8B8A8_TYPELESS            = 27,
	  R8G8B8A8_UNORM               = 28,
	  R8G8B8A8_UNORM_SRGB          = 29,
	  R8G8B8A8_UINT                = 30,
	  R8G8B8A8_SNORM               = 31,
	  R8G8B8A8_SINT                = 32,
	  R16G16_TYPELESS              = 33,
	  R16G16_FLOAT                 = 34,
	  R16G16_UNORM                 = 35,
	  R16G16_UINT                  = 36,
	  R16G16_SNORM                 = 37,
	  R16G16_SINT                  = 38,
	  R32_TYPELESS                 = 39,
	  D32_FLOAT                    = 40,
	  R32_FLOAT                    = 41,
	  R32_UINT                     = 42,
	  R32_SINT                     = 43,
	  R24G8_TYPELESS               = 44,
	  D24_UNORM_S8_UINT            = 45,
	  R24_UNORM_X8_TYPELESS        = 46,
	  X24_TYPELESS_G8_UINT         = 47,
	  R8G8_TYPELESS                = 48,
	  R8G8_UNORM                   = 49,
	  R8G8_UINT                    = 50,
	  R8G8_SNORM                   = 51,
	  R8G8_SINT                    = 52,
	  R16_TYPELESS                 = 53,
	  R16_FLOAT                    = 54,
	  D16_UNORM                    = 55,
	  R16_UNORM                    = 56,
	  R16_UINT                     = 57,
	  R16_SNORM                    = 58,
	  R16_SINT                     = 59,
	  R8_TYPELESS                  = 60,
	  R8_UNORM                     = 61,
	  R8_UINT                      = 62,
	  R8_SNORM                     = 63,
	  R8_SINT                      = 64,
	  A8_UNORM                     = 65,
	  R1_UNORM                     = 66,
	  R9G9B9E5_SHAREDEXP           = 67,
	  R8G8_B8G8_UNORM              = 68,
	  G8R8_G8B8_UNORM              = 69,
	  BC1_TYPELESS                 = 70,
	  BC1_UNORM                    = 71,
	  BC1_UNORM_SRGB               = 72,
	  BC2_TYPELESS                 = 73,
	  BC2_UNORM                    = 74,
	  BC2_UNORM_SRGB               = 75,
	  BC3_TYPELESS                 = 76,
	  BC3_UNORM                    = 77,
	  BC3_UNORM_SRGB               = 78,
	  BC4_TYPELESS                 = 79,
	  BC4_UNORM                    = 80,
	  BC4_SNORM                    = 81,
	  BC5_TYPELESS                 = 82,
	  BC5_UNORM                    = 83,
	  BC5_SNORM                    = 84,
	  B5G6R5_UNORM                 = 85,
	  B5G5R5A1_UNORM               = 86,
	  B8G8R8A8_UNORM               = 87,
	  B8G8R8X8_UNORM               = 88,
	  R10G10B10_XR_BIAS_A2_UNORM   = 89,
	  B8G8R8A8_TYPELESS            = 90,
	  B8G8R8A8_UNORM_SRGB          = 91,
	  B8G8R8X8_TYPELESS            = 92,
	  B8G8R8X8_UNORM_SRGB          = 93,
	  BC6H_TYPELESS                = 94,
	  BC6H_UF16                    = 95,
	  BC6H_SF16                    = 96,
	  BC7_TYPELESS                 = 97,
	  BC7_UNORM                    = 98,
	  BC7_UNORM_SRGB               = 99 
	};

	public enum class AlphaMode  
	{
		Unknown         = 0,
		Premultiplied   = 1,
		Straight        = 2,
		Ignore          = 3 
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct PixelFormat
	{
	private:
		DXGI_FORMAT     _format;
  		D2D1_ALPHA_MODE _alphaMode;
	public:
		initonly static PixelFormat Default = PixelFormat(DxgiFormat::UNKNOWN, AlphaMode::Unknown);

		PixelFormat(DxgiFormat format, AlphaMode alphaMode)
		{
			_format = (DXGI_FORMAT)format;
			_alphaMode = (D2D1_ALPHA_MODE)alphaMode;
		}
	internal:
		PixelFormat(const D2D1_PIXEL_FORMAT& pixelFormat)
		{
			_format = pixelFormat.format;
			_alphaMode = pixelFormat.alphaMode;
		}
	};

	public enum class RenderTargetType
	{
		Default = 0,
		Software = 1,
		Hardware = 2
	};

	public enum class RenderTargetUsage  
	{
		None                    = 0x00000000,
		ForceBitmapRemoting     = 0x00000001,
		GdiCompatible           = 0x00000002 
	};

	public enum class FeatureLevel 
	{
		Default   	  = 0,
		Level9        = D3D10_FEATURE_LEVEL_9_1,
		Level10       = D3D10_FEATURE_LEVEL_10_0 
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct RenderTargetProperties
	{
	private:
		D2D1_RENDER_TARGET_TYPE  _type;
		PixelFormat        		 _pixelFormat;
		FLOAT                    _dpiX;
		FLOAT                    _dpiY;
		D2D1_RENDER_TARGET_USAGE _usage;
		D2D1_FEATURE_LEVEL       _minLevel;
	public:
		initonly static RenderTargetProperties Default = RenderTargetProperties(
			RenderTargetType::Default,
			PixelFormat::Default,
			0, 0,
			RenderTargetUsage::None,
			FeatureLevel::Default
			);
		initonly static RenderTargetProperties Software = RenderTargetProperties(
			RenderTargetType::Software,
			PixelFormat::Default,
			0, 0,
			RenderTargetUsage::None,
			FeatureLevel::Default
			);

		initonly static RenderTargetProperties Remoting = RenderTargetProperties(
			RenderTargetType::Software,
			PixelFormat::Default,
			0, 0,
			RenderTargetUsage::ForceBitmapRemoting,
			FeatureLevel::Default
			);
		
		RenderTargetProperties(RenderTargetType type, PixelFormat pixelFormat, FLOAT dpiX, FLOAT dpiY, RenderTargetUsage usage, FeatureLevel minLevel)
		{
			_type = (D2D1_RENDER_TARGET_TYPE)type;
			_pixelFormat = pixelFormat;
			_dpiX = dpiX;
			_dpiY = dpiY;
			_usage = (D2D1_RENDER_TARGET_USAGE)usage;
			_minLevel = (D2D1_FEATURE_LEVEL)minLevel;
		}

	};

	public enum class PresentOptions
	{
		None              = 0x00000000,
		RetainContents    = 0x00000001,
		Immediately       = 0x00000002 
	};

	public enum class FactoryType  
	{
		SingleThreaded   = 0,
		MultiThreaded    = 1 
	};


	public enum class DebugLevel 
	{
		None          = 0,
		Error         = 1,
		Warning       = 2,
		Information   = 3 
	};

	[StructLayout(LayoutKind::Sequential)]
	public value struct WindowRenderTargetProperties
	{
	private:
		HWND _hwnd;
		SizeU _pixelSize;
		D2D1_PRESENT_OPTIONS _presentOptions;
	public:
		WindowRenderTargetProperties(System::IntPtr windowHandle, SizeU pixelSize, PresentOptions presentOptions)
		{
			_hwnd = (HWND)windowHandle.ToPointer();
			_pixelSize = pixelSize;
			_presentOptions = (D2D1_PRESENT_OPTIONS)presentOptions;
		}
	};


	public ref class Direct2DFactory
	{
	internal:
		Direct2DFactory(ID2D1Factory* factory)
		{
			_factory = factory;
		}

	public:
		~Direct2DFactory()
		{
			this->!Direct2DFactory();
		}

		!Direct2DFactory()
		{
			if(_factory)
			{
				_factory->Release();
				_factory = NULL;
			}
		}
	public:
		static Direct2DFactory^ CreateFactory(FactoryType factoryType, DebugLevel debugLevel);

		WindowRenderTarget^ CreateWindowRenderTarget(Control^ control);
		WindowRenderTarget^ CreateWindowRenderTarget(Control^ control, 
			PresentOptions presentOptions, 
			RenderTargetProperties renderTargetProperties);
		
		RenderTarget^ CreateWicBitmapRenderTarget(WicBitmap^ bitmap, RenderTargetProperties renderTargetProperties);
		DCRenderTarget^ CreateDCRenderTarget(RenderTargetProperties renderTargetProperties);

		StrokeStyle^ CreateStrokeStyle(StrokeStyleProperties properties, array<FLOAT>^ dashes);
		EllipseGeometry^ CreateEllipseGeometry(Ellipse ellipse);
		RectangleGeometry^ CreateRectangleGeometry(RectF rect);
		RoundedRectangleGeometry^ CreateRoundedRectangleGeometry(RoundedRect rect);
		TransformedGeometry^ CreateTransformedGeometry(Geometry^ sourceGeometry, Matrix3x2 transform);
		GeometryGroup^ CreateGeometryGroup(FillMode fillMode, array<Geometry^>^ geometries);
		PathGeometry^ CreatePathGeometry();

		void ReloadSystemMetrics()
		{
			HRESULT hr = _factory->ReloadSystemMetrics();
			if(FAILED(hr))
				Marshal::ThrowExceptionForHR(hr);
		}
		void GetDesktopDpi([OutAttribute()]System::Single% dpiX, [OutAttribute()]System::Single% dpiY)
		{
			FLOAT x;
			FLOAT y;
			_factory->GetDesktopDpi(&x, &y);
			dpiX = x;
			dpiY = y;
		}
	internal:
		inline ID2D1Factory* GetNative()
		{
			return _factory;
		}
	private: 
		ID2D1Factory* _factory;
	};
}}}
