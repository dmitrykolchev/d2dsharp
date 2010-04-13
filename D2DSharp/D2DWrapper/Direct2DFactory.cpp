// This is the main DLL file.

#include "stdafx.h"

#include "Direct2DFactory.h"
#include "WicBitmap.h"

namespace DykBits { namespace Graphics { namespace Direct2D 
{
	Direct2DFactory^ Direct2DFactory::CreateFactory(FactoryType factoryType, DebugLevel debugLevel)
	{
		D2D1_FACTORY_OPTIONS options = { (D2D1_DEBUG_LEVEL)debugLevel };

		ID2D1Factory* factory;

		D2D1CreateFactory((D2D1_FACTORY_TYPE)factoryType, __uuidof(ID2D1Factory), &options, (void**)&factory);

		return gcnew Direct2DFactory(factory);
	}

	RenderTarget^ Direct2DFactory::CreateWicBitmapRenderTarget(WicBitmap^ bitmap, RenderTargetProperties renderTargetProperties)
	{
		ID2D1RenderTarget *renderTarget;

		HRESULT hr = GetNative()->CreateWicBitmapRenderTarget(
			bitmap->GetNative(),
			(D2D1_RENDER_TARGET_PROPERTIES *)&renderTargetProperties,
			&renderTarget);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew RenderTarget(renderTarget);
	}

	DCRenderTarget^ Direct2DFactory::CreateDCRenderTarget(RenderTargetProperties renderTargetProperties)
	{
		ID2D1DCRenderTarget *renderTarget;

		HRESULT hr = GetNative()->CreateDCRenderTarget(
			(D2D1_RENDER_TARGET_PROPERTIES *)&renderTargetProperties,
			&renderTarget);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew DCRenderTarget(renderTarget);

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

		HRESULT hr = GetNative()->CreateHwndRenderTarget(
			(D2D1_RENDER_TARGET_PROPERTIES *)&renderTargetProperties,
			(D2D1_HWND_RENDER_TARGET_PROPERTIES *)&windowRenderTargetProperties,
			&renderTarget);

		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew WindowRenderTarget(renderTarget);
	}


	StrokeStyle^ Direct2DFactory::CreateStrokeStyle(StrokeStyleProperties properties, array<FLOAT>^ dashes)
	{
		UINT count = dashes != nullptr ? dashes->Length : 0;
		pin_ptr<FLOAT> p = dashes != nullptr ? &dashes[0] : nullptr;
		ID2D1StrokeStyle *native;
		HRESULT hr = GetNative()->CreateStrokeStyle(
			(D2D1_STROKE_STYLE_PROPERTIES *)&properties,
			p,
			count,
			&native);
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);
		return gcnew StrokeStyle(native);
	}

	EllipseGeometry^ Direct2DFactory::CreateEllipseGeometry(Ellipse ellipse)
	{
		ID2D1EllipseGeometry *ellipseGeometry;
		
		HRESULT hr = GetNative()->CreateEllipseGeometry((D2D1_ELLIPSE *)&ellipse, &ellipseGeometry);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew EllipseGeometry(ellipseGeometry);
	}

	RectangleGeometry^ Direct2DFactory::CreateRectangleGeometry(RectF rect)
	{
		ID2D1RectangleGeometry *geometry;
		
		HRESULT hr = GetNative()->CreateRectangleGeometry((D2D1_RECT_F *)&rect, &geometry);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew RectangleGeometry(geometry);
	}

	RoundedRectangleGeometry^ Direct2DFactory::CreateRoundedRectangleGeometry(RoundedRect rect)
	{
		ID2D1RoundedRectangleGeometry *geometry;
		
		HRESULT hr = GetNative()->CreateRoundedRectangleGeometry((D2D1_ROUNDED_RECT *)&rect, &geometry);
		
		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew RoundedRectangleGeometry(geometry);
	}

	TransformedGeometry^ Direct2DFactory::CreateTransformedGeometry(Geometry^ sourceGeometry, Matrix3x2 transform)
	{
		ID2D1TransformedGeometry *geometry;

		HRESULT hr = GetNative()->CreateTransformedGeometry(
			sourceGeometry->GetNative(),
			(D2D1_MATRIX_3X2_F*)&transform, 
			&geometry);

		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew TransformedGeometry(geometry);
	}

	GeometryGroup^ Direct2DFactory::CreateGeometryGroup(FillMode fillMode, array<Geometry^>^ geometries)
	{
		if(geometries == nullptr)
			throw gcnew ArgumentNullException("geometries");

		ID2D1GeometryGroup *geometry;

		pin_ptr<Geometry^> p = &geometries[0];

		HRESULT hr = GetNative()->CreateGeometryGroup(
			(D2D1_FILL_MODE)fillMode,
			(ID2D1Geometry **)p,
			geometries->Length,
			&geometry);

		if(FAILED(hr))
			Marshal::ThrowExceptionForHR(hr);

		return gcnew GeometryGroup(geometry);
	}
}}}