/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#include "stdafx.h"

#include "Direct2DFactory.h"
#include "WicBitmap.h"

namespace Managed { namespace Graphics { namespace Direct2D 
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

		ComUtils::CheckResult(GetNative()->CreateWicBitmapRenderTarget(
			bitmap->GetNative(),
			(D2D1_RENDER_TARGET_PROPERTIES *)&renderTargetProperties,
			&renderTarget));
		
		return gcnew RenderTarget(renderTarget);
	}

	DCRenderTarget^ Direct2DFactory::CreateDCRenderTarget(RenderTargetProperties renderTargetProperties)
	{
		ID2D1DCRenderTarget *renderTarget;

		ComUtils::CheckResult(GetNative()->CreateDCRenderTarget(
			(D2D1_RENDER_TARGET_PROPERTIES *)&renderTargetProperties,
			&renderTarget));
		
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

		ComUtils::CheckResult(GetNative()->CreateHwndRenderTarget(
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
		ComUtils::CheckResult(GetNative()->CreateStrokeStyle(
			(D2D1_STROKE_STYLE_PROPERTIES *)&properties,
			p,
			count,
			&native));
		return gcnew StrokeStyle(native);
	}

	PathGeometry^ Direct2DFactory::CreatePathGeometry()
	{
		ID2D1PathGeometry *geometry;
		
		ComUtils::CheckResult(GetNative()->CreatePathGeometry(&geometry));
		
		return gcnew PathGeometry(geometry);
	}

	EllipseGeometry^ Direct2DFactory::CreateEllipseGeometry(Ellipse ellipse)
	{
		ID2D1EllipseGeometry *ellipseGeometry;
		
		ComUtils::CheckResult(GetNative()->CreateEllipseGeometry((D2D1_ELLIPSE *)&ellipse, &ellipseGeometry));

		return gcnew EllipseGeometry(ellipseGeometry);
	}

	RectangleGeometry^ Direct2DFactory::CreateRectangleGeometry(RectF rect)
	{
		ID2D1RectangleGeometry *geometry;
		
		ComUtils::CheckResult(GetNative()->CreateRectangleGeometry((D2D1_RECT_F *)&rect, &geometry));
		
		return gcnew RectangleGeometry(geometry);
	}

	RoundedRectangleGeometry^ Direct2DFactory::CreateRoundedRectangleGeometry(RoundedRect rect)
	{
		ID2D1RoundedRectangleGeometry *geometry;
		
		ComUtils::CheckResult(GetNative()->CreateRoundedRectangleGeometry((D2D1_ROUNDED_RECT *)&rect, &geometry));

		return gcnew RoundedRectangleGeometry(geometry);
	}

	TransformedGeometry^ Direct2DFactory::CreateTransformedGeometry(Geometry^ sourceGeometry, Matrix3x2 transform)
	{
		ID2D1TransformedGeometry *geometry;

		ComUtils::CheckResult(GetNative()->CreateTransformedGeometry(
			sourceGeometry->GetNative(),
			(D2D1_MATRIX_3X2_F*)&transform, 
			&geometry));

		return gcnew TransformedGeometry(geometry);
	}

	GeometryGroup^ Direct2DFactory::CreateGeometryGroup(FillMode fillMode, array<Geometry^>^ geometries)
	{
		if(geometries == nullptr)
			throw gcnew ArgumentNullException("geometries");

		ID2D1GeometryGroup *geometry;

		pin_ptr<Geometry^> p = &geometries[0];

		ComUtils::CheckResult(GetNative()->CreateGeometryGroup(
			(D2D1_FILL_MODE)fillMode,
			(ID2D1Geometry **)p,
			geometries->Length,
			&geometry));

		return gcnew GeometryGroup(geometry);
	}
}}}