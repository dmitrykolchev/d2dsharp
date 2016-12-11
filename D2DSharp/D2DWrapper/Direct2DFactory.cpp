/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "stdafx.h"

#include "Direct2DFactory.h"
#include "WicBitmap.h"
#include "DxgiWrapper.h"
#include "Device.h"

namespace Managed { namespace Graphics { namespace Direct2D 
{
	Direct2DFactory^ Direct2DFactory::CreateFactory(FactoryType factoryType, DebugLevel debugLevel)
	{
		D2D1_FACTORY_OPTIONS options = { (D2D1_DEBUG_LEVEL)debugLevel };

		ID2D1Factory* factory;

		D2D1CreateFactory((D2D1_FACTORY_TYPE)factoryType, __uuidof(ID2D1Factory), &options, reinterpret_cast<void**>(&factory));

		return gcnew Direct2DFactory(factory);
	}

	Direct2DFactory^ Direct2DFactory::CreateFactory(FactoryType factoryType, DebugLevel debugLevel, FactoryVersion version)
	{
		D2D1_FACTORY_OPTIONS options = { (D2D1_DEBUG_LEVEL) debugLevel };
		if (version == FactoryVersion::Auto)
		{
			ID2D1Factory1* factory1;
			HRESULT hr = D2D1CreateFactory((D2D1_FACTORY_TYPE) factoryType, __uuidof(ID2D1Factory1), &options, reinterpret_cast<void**>(&factory1));
			if (SUCCEEDED(hr))
				return gcnew Direct2DFactory1(factory1);
			ID2D1Factory* factory;
			ComUtils::CheckResult(D2D1CreateFactory((D2D1_FACTORY_TYPE) factoryType, __uuidof(ID2D1Factory), &options, reinterpret_cast<void**>(&factory)));
			return gcnew Direct2DFactory(factory);
		}
		else if (version == FactoryVersion::V_1)
		{
			ID2D1Factory* factory;
			ComUtils::CheckResult(D2D1CreateFactory((D2D1_FACTORY_TYPE) factoryType, __uuidof(ID2D1Factory), &options, reinterpret_cast<void**>(&factory)));
			return gcnew Direct2DFactory(factory);
		}
		else if (version == FactoryVersion::V_2)
		{
			ID2D1Factory1* factory1;
			ComUtils::CheckResult(D2D1CreateFactory((D2D1_FACTORY_TYPE) factoryType, __uuidof(ID2D1Factory1), &options, reinterpret_cast<void**>(&factory1)));
			return gcnew Direct2DFactory1(factory1);
		}
		throw gcnew ArgumentOutOfRangeException("version");
	}
	Device^ Direct2DFactory::CreateDevice(DxgiDevice^ dxgiDevice)
	{
		ID2D1Device* device;
		ComUtils::CheckResult(GetNative<ID2D1Factory1>()->CreateDevice(dxgiDevice->GetNative<IDXGIDevice>(), &device));
		return gcnew Device(device);
	}
	RenderTarget^ Direct2DFactory::CreateWicBitmapRenderTarget(WicBitmap^ bitmap, RenderTargetProperties renderTargetProperties)
	{
		ID2D1RenderTarget *renderTarget;

		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateWicBitmapRenderTarget(
			bitmap->GetNative<IWICBitmap>(),
			(D2D1_RENDER_TARGET_PROPERTIES *)&renderTargetProperties,
			&renderTarget));
		
		return gcnew RenderTarget(renderTarget);
	}

	DCRenderTarget^ Direct2DFactory::CreateDCRenderTarget(RenderTargetProperties renderTargetProperties)
	{
		ID2D1DCRenderTarget *renderTarget;

		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateDCRenderTarget(
			(D2D1_RENDER_TARGET_PROPERTIES *)&renderTargetProperties,
			&renderTarget));
		
		return gcnew DCRenderTarget(renderTarget);
	}

	RenderTarget^ Direct2DFactory::CreateDxGiSurfaceRenderTarget(DxgiSurface^ surface, RenderTargetProperties renderTargetProperties)
	{
		ID2D1RenderTarget* renderTarget;
		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateDxgiSurfaceRenderTarget(surface->GetNative<IDXGISurface>(), 
			(D2D1_RENDER_TARGET_PROPERTIES *)&renderTargetProperties,
			&renderTarget));
		return gcnew RenderTarget(renderTarget);
	}

	WindowRenderTarget^ Direct2DFactory::CreateWindowRenderTarget(Control^ control)
	{
		return CreateWindowRenderTarget(control, PresentOptions::None, RenderTargetProperties::Default);
	}

	WindowRenderTarget^ Direct2DFactory::CreateWindowRenderTarget(Control^ control, 
			PresentOptions presentOptions, 
			RenderTargetProperties renderTargetProperties)
	{
		System::Drawing::Size size = control->ClientSize;
		
		SizeU sizeu = SizeU(size.Width, size.Height);

		WindowRenderTargetProperties windowRenderTargetProperties = WindowRenderTargetProperties(
			control->Handle, sizeu, presentOptions);

		ID2D1HwndRenderTarget *renderTarget;

		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateHwndRenderTarget(
			(D2D1_RENDER_TARGET_PROPERTIES *)&renderTargetProperties,
			(D2D1_HWND_RENDER_TARGET_PROPERTIES *)&windowRenderTargetProperties,
			&renderTarget));

		return gcnew WindowRenderTarget(renderTarget);
	}


	StrokeStyle^ Direct2DFactory::CreateStrokeStyle(StrokeStyleProperties properties, array<FLOAT>^ dashes)
	{
		UINT count = dashes != nullptr ? dashes->Length : 0;
		pin_ptr<FLOAT> p = dashes != nullptr ? &dashes[0] : nullptr;
		ID2D1StrokeStyle *native;
		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateStrokeStyle(
			(D2D1_STROKE_STYLE_PROPERTIES *)&properties,
			p,
			count,
			&native));
		return gcnew StrokeStyle(native);
	}

	StrokeStyle^ Direct2DFactory::CreateStrokeStyle(StrokeStyleProperties1 properties, array<FLOAT>^ dashes)
	{
		throw gcnew NotSupportedException();
	}

	StrokeStyle^ Direct2DFactory1::CreateStrokeStyle(StrokeStyleProperties1 properties, array<FLOAT>^ dashes)
	{
		UINT count = dashes != nullptr ? dashes->Length : 0;
		pin_ptr<FLOAT> p = dashes != nullptr ? &dashes[0] : nullptr;
		ID2D1StrokeStyle1 *native;
		ComUtils::CheckResult(GetNative<ID2D1Factory1>()->CreateStrokeStyle(
			(D2D1_STROKE_STYLE_PROPERTIES1 *) &properties,
			p,
			count,
			&native));
		return gcnew StrokeStyle1(native);
	}

	PathGeometry^ Direct2DFactory::CreatePathGeometry()
	{
		ID2D1PathGeometry *geometry;
		
		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreatePathGeometry(&geometry));
		
		return gcnew PathGeometry(geometry);
	}

	PathGeometry^ Direct2DFactory1::CreatePathGeometry()
	{
		ID2D1PathGeometry1 *geometry;

		ComUtils::CheckResult(GetNative<ID2D1Factory1>()->CreatePathGeometry(&geometry));

		return gcnew PathGeometry1(geometry);
	}


	EllipseGeometry^ Direct2DFactory::CreateEllipseGeometry(Ellipse ellipse)
	{
		ID2D1EllipseGeometry *ellipseGeometry;
		
		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateEllipseGeometry((D2D1_ELLIPSE *) &ellipse, &ellipseGeometry));

		return gcnew EllipseGeometry(ellipseGeometry);
	}

	RectangleGeometry^ Direct2DFactory::CreateRectangleGeometry(RectF rect)
	{
		ID2D1RectangleGeometry *geometry;
		
		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateRectangleGeometry((D2D1_RECT_F *) &rect, &geometry));
		
		return gcnew RectangleGeometry(geometry);
	}

	RoundedRectangleGeometry^ Direct2DFactory::CreateRoundedRectangleGeometry(RoundedRect rect)
	{
		ID2D1RoundedRectangleGeometry *geometry;
		
		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateRoundedRectangleGeometry((D2D1_ROUNDED_RECT *) &rect, &geometry));

		return gcnew RoundedRectangleGeometry(geometry);
	}

	TransformedGeometry^ Direct2DFactory::CreateTransformedGeometry(Geometry^ sourceGeometry, Matrix3x2 transform)
	{
		ID2D1TransformedGeometry *geometry;

		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateTransformedGeometry(
			sourceGeometry->GetNative<ID2D1Geometry>(),
			(D2D1_MATRIX_3X2_F*)&transform, 
			&geometry));

		return gcnew TransformedGeometry(geometry);
	}

	GeometryGroup^ Direct2DFactory::CreateGeometryGroup(FillMode fillMode, array<Geometry^>^ geometries)
	{
		if(geometries == nullptr)
			throw gcnew ArgumentNullException("geometries");

		ID2D1GeometryGroup *geometry;
		
		array<ID2D1Geometry*>^ temp = gcnew array<ID2D1Geometry*>(geometries->Length);

		for (int index = 0; index < geometries->Length; ++index)
			temp[index] = geometries[index]->GetNative<ID2D1Geometry>();
		pin_ptr<ID2D1Geometry*> p = &temp[0];

		ComUtils::CheckResult(GetNative<ID2D1Factory>()->CreateGeometryGroup(
			(D2D1_FILL_MODE)fillMode,
			p,
			geometries->Length,
			&geometry));

		return gcnew GeometryGroup(geometry);
	}
}}}