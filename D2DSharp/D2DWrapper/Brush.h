/* 
* 
* Authors: 
*  Dmitry Kolchev <dmitrykolchev@msn.com>
*  
*/
#pragma once

#include "D2DCommon.h"
#include "D2DResource.h"
#include "Color.h"

namespace Managed { namespace Graphics { namespace Direct2D 
{
	[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
	public value struct GradientStop
	{
	private:
		FLOAT _position;
		Color _color;
	public:
		GradientStop(FLOAT position, Color color)
		{
			_position = position;
			_color = color;
		}

		property FLOAT Position
		{
			FLOAT get() { return _position; }
		}

		property Managed::Graphics::Direct2D::Color Color
		{
			Managed::Graphics::Direct2D::Color get() { return _color; }
		}
	};

	[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
	public value struct BrushProperties
	{
	private:
		FLOAT _opacity;
		Matrix3x2 _transform;
	public:
		initonly static BrushProperties Default = BrushProperties(1, Matrix3x2::Identity);

		BrushProperties(FLOAT opacity, Matrix3x2 transform)
		{
			_opacity = opacity;
			_transform = transform;
		}

		property FLOAT Opacity
		{
			FLOAT get() { return _opacity; }
		}

		property Matrix3x2 Transform
		{
			Matrix3x2 get() { return _transform; }
		}
	};

	public ref class Brush abstract: D2DResource
	{
	protected:
		Brush(ID2D1Brush* native): 
			 D2DResource(native)
		{
		}
	public:
		property FLOAT Opacity
		{
			FLOAT get()
			{
				return GetNative<ID2D1Brush>()->GetOpacity();
			}
			void set(FLOAT value)
			{
				GetNative<ID2D1Brush>()->SetOpacity(value);
			}
		}

		property Matrix3x2 Transform
		{
			Matrix3x2 get()
			{
				Matrix3x2 m;
				GetNative<ID2D1Brush>()->GetTransform(reinterpret_cast<D2D1_MATRIX_3X2_F*>(&m));
				return m;
			}
			void set(Matrix3x2 value)
			{
				GetNative<ID2D1Brush>()->SetTransform((D2D1_MATRIX_3X2_F*) &value);
			}
		}
	};
}}}